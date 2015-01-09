#include "jcpp/net/JInet6Address.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/io/JInvalidObjectException.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::native::api;
using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp {
	namespace net {

		jint JInet6Address::INADDRSZ = 16;

		JInet6Address::JInet6Address() : JInetAddress(getClazz(), new JPrimitiveInt(IPv6)) {
			ipaddress = new JPrimitiveByteArray(INADDRSZ);
			scope_id_set = false;
			scope_id = 0;
			scope_ifname_set = false;
			ifname = null;
		}

		JInet6Address::JInet6Address(JString* _hostName, JPrimitiveByteArray* addr) : JInetAddress(getClazz(), new JPrimitiveInt(IPv4)) {
			hostName = _hostName;
			ipaddress = new JPrimitiveByteArray(INADDRSZ);
			scope_id_set = false;
			scope_id = 0;
			scope_ifname_set = false;
			ifname = null;

			if (addr != null) {
				if (addr->size() == 6) {
					for(jint index = 0; index < INADDRSZ; index++) {
						ipaddress->setByte(index, addr->getByte(index));
					}
				}
			}
		}

		jbool JInet6Address::isIPv4CompatibleAddress() {
			if ((ipaddress->getByte(0) == 0x00) && (ipaddress->getByte(1) == 0x00) &&
				(ipaddress->getByte(2) == 0x00) && (ipaddress->getByte(3) == 0x00) &&
				(ipaddress->getByte(4) == 0x00) && (ipaddress->getByte(5) == 0x00) &&
				(ipaddress->getByte(6) == 0x00) && (ipaddress->getByte(7) == 0x00) &&
				(ipaddress->getByte(8) == 0x00) && (ipaddress->getByte(9) == 0x00) &&
				(ipaddress->getByte(10) == 0x00) && (ipaddress->getByte(11) == 0x00))  {
				return true;
			}
			return false;
		}

		jbool JInet6Address::isMulticastAddress() {
			return ((ipaddress->getByte(0) & 0xff) == 0xff);
		}

		jbool JInet6Address::isAnyLocalAddress() {
			jbyte test = 0x00;
			for (jint i = 0; i < INADDRSZ; i++) {
				test |= ipaddress->getByte(i);
			}
			return (test == 0x00);
		}

		jbool JInet6Address::isLoopbackAddress() {
			jbyte test = 0x00;
			for (jint i = 0; i < 15; i++) {
				test |= ipaddress->getByte(i);
			}
			return (test == 0x00) && (ipaddress->getByte(15) == 0x01);
		}

		jbool JInet6Address::isLinkLocalAddress() {
            return ((ipaddress->getByte(0) & 0xff) == 0xfe && (ipaddress->getByte(1) & 0xc0) == 0x80);
		}

		jbool JInet6Address::isSiteLocalAddress() {
			return ((ipaddress->getByte(0) & 0xff) == 0xfe && (ipaddress->getByte(1) & 0xc0) == 0xc0);
		}

		jbool JInet6Address::isMCGlobal() {
			return ((ipaddress->getByte(0) & 0xff) == 0xff && (ipaddress->getByte(1) & 0x0f) == 0x0e);
		}

		jbool JInet6Address::isMCNodeLocal() {
			return ((ipaddress->getByte(0) & 0xff) == 0xff && (ipaddress->getByte(1) & 0x0f) == 0x01);
		}

		jbool JInet6Address::isMCLinkLocal() {
			return ((ipaddress->getByte(0) & 0xff) == 0xff && (ipaddress->getByte(1) & 0x0f) == 0x02);
		}

		jbool JInet6Address::isMCSiteLocal() {
			return ((ipaddress->getByte(0) & 0xff) == 0xff && (ipaddress->getByte(1) & 0x0f) == 0x05);
		}

		jbool JInet6Address::isMCOrgLocal() {
            return ((ipaddress->getByte(0) & 0xff) == 0xff && (ipaddress->getByte(1) & 0x0f) == 0x08);
		}

		JPrimitiveByteArray* JInet6Address::getAddress() {
			return ipaddress->clone();
		}

		JString* JInet6Address::getHostAddress() {
			JStringBuilder* sb = new JStringBuilder();

			for (jint i = 0; i < (INADDRSZ / 2); i++) {
				jint n = ((ipaddress->getByte(i<<1)<<8) & 0xff00) | (ipaddress->getByte((i<<1)+1) & 0xff);
				sb->append(JInteger::toHexString(n));
				if (i < (INADDRSZ / 2) -1 ) {
				   sb->append(":");
				}
			}

			if (scope_ifname_set) { /* must check this first */
				sb->append("%")->append(ifname);
			} else if (scope_id_set) {
				sb->append("%")->append(scope_id);
			}
			return sb->toString();
		}

		jint JInet6Address::hashCode() {
			if (ipaddress != null) {
				int hash = 0;
				int i=0;
				while (i<INADDRSZ) {
					int j=0;
					int component=0;
					while (j<4 && i<INADDRSZ) {
						component = (component << 8) + ipaddress->getByte(i);
						j++;
						i++;
					}
					hash += component;
				}
				return hash;

			} else {
				return 0;
			}
		}

		jbool JInet6Address::equals(JObject* obj) {
			if ((obj == null) || obj->getClass()!=getClazz()){
				return false;
			}
			JInet6Address* other = dynamic_cast<JInet6Address*>(obj);
            for (int i = 0; i < INADDRSZ; i++) {
                if (ipaddress->getByte(i) != other->ipaddress->getByte(i)) {
                    return false;
                }
            }
            return true;
		}

		JPrimitiveObjectArray* JInet6Address::serialPersistentFields = null;

        JPrimitiveObjectArray* JInet6Address::getSerialPersistentFields(){
            if (serialPersistentFields==null){
                serialPersistentFields=new JPrimitiveObjectArray(JObjectStreamField::getClazz(),5);
                serialPersistentFields->set(0,new JObjectStreamField(new JString("ipaddress"), JPrimitiveByteArray::getClazz()));
                serialPersistentFields->set(1,new JObjectStreamField(new JString("scope_id"), JPrimitiveInt::getClazz()));
        		serialPersistentFields->set(2,new JObjectStreamField(new JString("scope_id_set"), JPrimitiveBoolean::getClazz()));
        		serialPersistentFields->set(3,new JObjectStreamField(new JString("scope_ifname_set"), JPrimitiveBoolean::getClazz()));
        		serialPersistentFields->set(4,new JObjectStreamField(new JString("ifname"), JString::getClazz()));
            }
            return serialPersistentFields;
        }

		void JInet6Address::readObject(JObjectInputStream* in){
        	JObjectInputStream::JGetField* gf = in->readFields();
        	ipaddress = dynamic_cast<JPrimitiveByteArray*>(gf->get(new JString("ipaddress"), (JObject*)null));
        	scope_id = gf->get(new JString("scope_id"),(jint) -1);
        	scope_id_set = gf->get(new JString("scope_id_set"), false);
        	scope_ifname_set = gf->get(new JString("scope_ifname_set"), false);
        	ifname = dynamic_cast<JString*>(gf->get(new JString("ifname"), (JObject*)null));
	        if (ipaddress->size() != INADDRSZ) {
	            throw new JInvalidObjectException(new JString("invalid address length: "));
	        }
	        if (family->get() != IPv6) {
	            throw new JInvalidObjectException(new JString("invalid address family type"));
	        }
    	}

    	void JInet6Address::writeObject(JObjectOutputStream* out){
        	if (ifname != null) {
            	scope_ifname_set = true;
        	}
        	JObjectOutputStream::JPutField* pfields = out->putFields();
        	pfields->put(new JString("ipaddress"), ipaddress);
	        pfields->put(new JString("scope_id"), scope_id);
	        pfields->put(new JString("scope_id_set"), scope_id_set);
	        pfields->put(new JString("scope_ifname_set"), scope_ifname_set);
	        pfields->put(new JString("ifname"), ifname);
	        out->writeFields();
	    }

		JInet6Address::~JInet6Address() {
		}
	}
}
