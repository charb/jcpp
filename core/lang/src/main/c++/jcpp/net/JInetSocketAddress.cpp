#include "jcpp/net/JInetSocketAddress.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::native::api;

namespace jcpp {
	namespace net {



		JInetSocketAddress* JInetSocketAddress::createUnresolved(JString* host, jint port) {
			return new JInetSocketAddress(checkPort(port), checkHost(host));
		}

		jint JInetSocketAddress::checkPort(jint port) {
			if(port < 0 || port > 0xFFFF) {
				throw new JIllegalArgumentException((new JStringBuilder())->append("port out of range:")->append(port)->toString());
			}
			return port;
		}

		JString* JInetSocketAddress::checkHost(JString* hostname) {
			if(hostname == null) {
				throw new JIllegalArgumentException(new JString("hostname can't be null"));
			}
			return hostname;
		}

		JInetSocketAddress::JInetSocketAddress() : JSocketAddress(getClazz()) {
			port = new JPrimitiveInt(0);
			hostname = null;
			addr = null;
		}

		JInetSocketAddress::JInetSocketAddress(jint _port, JString* _hostname) : JSocketAddress(getClazz()) {
			port = new JPrimitiveInt(_port);
			hostname = _hostname;
			addr = null;
		}

		JInetSocketAddress::JInetSocketAddress(jint _port) : JSocketAddress(getClazz()) {
			hostname = null;
			addr = JInetAddress::anyLocalAddress();
			port = new JPrimitiveInt(checkPort(_port));
		}

		JInetSocketAddress::JInetSocketAddress(JInetAddress* _addr, jint _port) : JSocketAddress(getClazz()) {
			hostname = null;
			addr = _addr == null ? JInetAddress::anyLocalAddress() : _addr;
			port = new JPrimitiveInt(checkPort(_port));
		}

		JInetSocketAddress::JInetSocketAddress(JString* _hostname, jint _port) : JSocketAddress(getClazz()) {
			checkHost(_hostname);
			JInetAddress* _addr = null;
			JString* host = null;
			try {
				_addr = JInetAddress::getByName(_hostname);
			} catch(...) {
				host = _hostname;
			}
			hostname = host;
			addr = _addr;
			port = new JPrimitiveInt(checkPort(_port));
		}

		jint JInetSocketAddress::getPort() {
			return port->get();
		}

		JInetAddress* JInetSocketAddress::getAddress() {
			return addr;
		}

		JString* JInetSocketAddress::getHostName() {
			if (hostname != null)
				return hostname;
			if (addr != null)
				return addr->getHostName();
			return null;
		}

		JString* JInetSocketAddress::getHostString() {
			if (hostname != null)
				return hostname;
			if (addr != null) {
				if (addr->getHostNameWithoutResolving() != null) {
					return addr->getHostNameWithoutResolving();
				} else {
					return addr->getHostAddress();
				}
			}
			return null;
		}

		jbool JInetSocketAddress::isUnresolved() {
			return addr == null;
		}

		JString* JInetSocketAddress::toString() {
			if(addr == null) {
				return (new JStringBuilder())->append(hostname)->append(":")->append(port->get())->toString();
			} else {
				return (new JStringBuilder())->append(addr->toString())->append(":")->append(port->get())->toString();
			}
		}

		jbool JInetSocketAddress::equals(JObject* obj) {
			if ((obj == null) || obj->getClass()!=getClazz()){
				return false;
			}
			JInetSocketAddress* that = dynamic_cast<JInetSocketAddress*>(obj);
			jbool sameIP = false;
			if (addr != null) {
				sameIP = addr->equals(that->addr);
			} else if (hostname != null) {
				sameIP = (that->addr == null) && hostname->equalsIgnoreCase(that->hostname);
			} else {
				sameIP = (that->addr == null) && (that->hostname == null);
			}
			return sameIP && (port->get() == that->port->get());
		}

		jint JInetSocketAddress::hashCode() {
			if (addr != null)
				return addr->hashCode() + port->get();
			if (hostname != null)
				return hostname->toLowerCase()->hashCode() + port->get();
			return port->get();
		}

		JPrimitiveObjectArray* JInetSocketAddress::serialPersistentFields = null;

        JPrimitiveObjectArray* JInetSocketAddress::getSerialPersistentFields(){
            if (serialPersistentFields==null){
                serialPersistentFields=new JPrimitiveObjectArray(JObjectStreamField::getClazz(),3);
                serialPersistentFields->set(0,new JObjectStreamField(new JString("hostname"), JString::getClazz()));
                serialPersistentFields->set(1,new JObjectStreamField(new JString("addr"), JInetAddress::getClazz()));
        		serialPersistentFields->set(2,new JObjectStreamField(new JString("port"), JPrimitiveInt::getClazz()));
            }
            return serialPersistentFields;
        }

		void JInetSocketAddress::readObject(JObjectInputStream* in){
        	JObjectInputStream::JGetField* gf = in->readFields();
        	hostname = dynamic_cast<JString*>(gf->get(new JString("hostname"), (JObject*)null));
        	addr= dynamic_cast<JInetAddress*>(gf->get(new JString("addr"), (JObject*)null));
        	port->set(gf->get(new JString("port"), -1));
    	}

    	void JInetSocketAddress::writeObject(JObjectOutputStream* out){
        	JObjectOutputStream::JPutField* pf = out->putFields();
         	pf->put(new JString("hostname"), hostname);
         	pf->put(new JString("addr"), addr);
         	pf->put(new JString("port"), port->get());
         	out->writeFields();
	    }

		JInetSocketAddress::~JInetSocketAddress() {
		}

	}
}
