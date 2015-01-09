#include "jcpp/net/JInetAddress.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/net/JInet4Address.h"
#include "jcpp/net/JInet6Address.h"
#include "jcpp/net/JUnknownHostException.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::native::api;
using namespace jcpp::native::api::net;

namespace jcpp {
	namespace net {

		JInetAddress* JInetAddress::anyLocalAddress() {
			return new JInet4Address(new JString("0.0.0.0"), 0);
		}

		jbool JInetAddress::isIPv4MappedAddress(JPrimitiveByteArray* addr) {
			if (addr->size() < 16) {
				return false;
			}
			if ((addr->getByte(0) == 0x00) && (addr->getByte(1) == 0x00) &&
				(addr->getByte(2) == 0x00) && (addr->getByte(3) == 0x00) &&
				(addr->getByte(4) == 0x00) && (addr->getByte(5) == 0x00) &&
				(addr->getByte(6) == 0x00) && (addr->getByte(7) == 0x00) &&
				(addr->getByte(8) == 0x00) && (addr->getByte(9) == 0x00) &&
				(addr->getByte(10) == (jbyte)0xff) &&
				(addr->getByte(11) == (jbyte)0xff))  {
				return true;
			}
			return false;
		}

		JPrimitiveByteArray* JInetAddress::convertFromIPv4MappedAddress(JPrimitiveByteArray* addr) {
			if (isIPv4MappedAddress(addr)) {
				JPrimitiveByteArray* newAddr = new JPrimitiveByteArray(4);
				for(jint i = 0; i < 4; i++) {
					newAddr->setByte(i, addr->getByte(12 + i));
				}
				return newAddr;
			}
			return null;
		}

		JInetAddress* JInetAddress::getByAddress(JString* host, JPrimitiveByteArray* addr) {
			if (host != null && host->length() > 0 && host->charAt(0) == '[') {
				if (host->charAt(host->length()-1) == ']') {
					host = host->substring(1, host->length() -1);
				}
			}
			if (addr != null) {
				if (addr->size() == 4) {
					return new JInet4Address(host, addr);
				} else if (addr->size() == 16) {
					JPrimitiveByteArray* newAddr = convertFromIPv4MappedAddress(addr);
					if (newAddr != null) {
						return new JInet4Address(host, newAddr);
					} else {
						return new JInet6Address(host, addr);
					}
				}
			}
			throw new JUnknownHostException(new JString("addr is of illegal length"));
		}

		JInetAddress* JInetAddress::createInetAddress(const NativeInetAddress& nativeInetAddress) {
			if(nativeInetAddress.getFamily() == IPV4_FAMILY) {
				jbyte nativeIP[4];
				nativeInetAddress.getAddress(nativeIP);

				JPrimitiveByteArray* addr = new JPrimitiveByteArray(4);
				for(jint i = 0; i < 4; i++) {
					addr->setByte(i, nativeIP[i]);
				}

				return new JInet4Address(new JString(nativeInetAddress.getHostName()), addr);
			} else if(nativeInetAddress.getFamily() == IPV6_FAMILY) {
				jbyte nativeIP[16];
				nativeInetAddress.getAddress(nativeIP);

				JPrimitiveByteArray* addr = new JPrimitiveByteArray(16);
				for(jint i = 0; i < 16; i++) {
					addr->setByte(i, nativeIP[i]);
				}

				return new JInet6Address(new JString(nativeInetAddress.getHostName()), addr);
			}
			return null;
		}

		JInetAddress* JInetAddress::getByName(JString* host) {
			JInetAddress* address = null;
			if(host == null)  {
				address = getLoopbackAddress();
			} else {
				TRY_CATCH_NATIVE_EXCEPTION({ address = createInetAddress(NativeFactory::getNativeNetFactory()->getInetAddressByName(host->getNativeString())); })
			}
			return address;
		}

		JPrimitiveObjectArray* JInetAddress::getAllByName(JString* host) {
			JPrimitiveObjectArray* addresses = null;
			TRY_CATCH_NATIVE_EXCEPTION({
				std::vector<NativeInetAddress> nativeAddresses;
				NativeFactory::getNativeNetFactory()->getAllInetAddressesByName(nativeAddresses, host->getNativeString());

				addresses = new JPrimitiveObjectArray(JInetAddress::getClazz(), nativeAddresses.size());
				for(jint index = 0; index < nativeAddresses.size(); index++) {
					addresses->set(index, createInetAddress(nativeAddresses[index]));
				}
			})
			return addresses;
		}


		JInetAddress* JInetAddress::getLoopbackAddress() {
			JInetAddress* address = null;
			TRY_CATCH_NATIVE_EXCEPTION({ address = createInetAddress(NativeFactory::getNativeNetFactory()->getLoopbackAddress()); })
			return address;
		}

		JInetAddress* JInetAddress::getByAddress(JPrimitiveByteArray* addr) {
			if((addr == null) || ((addr->size() != 4) && (addr->size() != 16)) ) {
				throw new JUnknownHostException(new JString("addr is of illegal length"));
			}
			JInetAddress* address = null;
			TRY_CATCH_NATIVE_EXCEPTION({ address = createInetAddress(NativeFactory::getNativeNetFactory()->getInetAddressByAddress(addr->getArray(), addr->size() == 16 ? IPV6_FAMILY : IPV4_FAMILY)); })
			return address;
		}

		JInetAddress* JInetAddress::getLocalHost() {
			JInetAddress* address = null;
			TRY_CATCH_NATIVE_EXCEPTION({ address = createInetAddress(NativeFactory::getNativeNetFactory()->getLocalHost()); })
			return address;
		}

		jint JInetAddress::IPv4 = 1;

		jint JInetAddress::IPv6 = 2;

		JInetAddress::JInetAddress() : JObject(getClazz()) {
			hostName = null;
			address = new JPrimitiveInt();
			family = new JPrimitiveInt(IPv4);
		}

		JInetAddress::JInetAddress(JClass* _clazz, JPrimitiveInt* _family) : JObject(_clazz) {
			hostName = null;
			address = new JPrimitiveInt();
			family = _family;
		}

		JObject* JInetAddress::readResolve(){
			return new JInet4Address(getHostName(),getAddress());
		}

		jbool JInetAddress::isMulticastAddress() {
			return false;
		}

		jbool JInetAddress::isAnyLocalAddress() {
			return false;
		}

		jbool JInetAddress::isLoopbackAddress() {
			return false;
		}

		jbool JInetAddress::isLinkLocalAddress() {
			return false;
		}

		jbool JInetAddress::isSiteLocalAddress() {
			return false;
		}

		jbool JInetAddress::isMCGlobal() {
			return false;
		}

		jbool JInetAddress::isMCNodeLocal() {
			return false;
		}

		jbool JInetAddress::isMCLinkLocal() {
			return false;
		}

		jbool JInetAddress::isMCSiteLocal() {
			return false;
		}

		jbool JInetAddress::isMCOrgLocal() {
			return false;
		}

		JString* JInetAddress::getHostName() {
			if(hostName == null) {
				JPrimitiveByteArray* addr = getAddress();
				if(addr != null) {
					try {
						NativeInetAddress nativeAddress = NativeFactory::getNativeNetFactory()->getInetAddressByAddress(addr->getArray(), family->get() == IPv4 ? IPV4_FAMILY : IPV6_FAMILY);
						hostName = new JString(nativeAddress.getHostName());
					} catch(...) {
						// ignore
					}
				}
			}
			return hostName;
		}

		JPrimitiveByteArray* JInetAddress::getAddress() {
			return null;
		}

		JString* JInetAddress::getHostAddress() {
			return null;
		}

		jint JInetAddress::hashCode() {
			return -1;
		}

		jbool JInetAddress::equals(JObject* o) {
			return false;
		}

		JString* JInetAddress::toString() {
			JStringBuilder* sb = new JStringBuilder();
			if(hostName != null) {
				sb->append(hostName);
			}
			sb->append('/');
			JString* ha=getHostAddress();
			return sb->append(ha)->toString();
		}

		JString* JInetAddress::getHostNameWithoutResolving() {
			return hostName;
		}

		NativeInetAddress JInetAddress::createNativeInetAddress() {
			JString* hostName = getHostName();
			JString* hostAddress = getHostAddress();
			JPrimitiveByteArray* address = getAddress();
			return NativeInetAddress(
					hostName == null ? NativeString() : hostName->getNativeString() ,
					hostAddress == null ? NativeString() : hostAddress->getNativeString(),
					family->get() == IPv4 ? IPV4_FAMILY: IPV6_FAMILY,
					address->getArray());

		}

		JPrimitiveObjectArray* JInetAddress::serialPersistentFields = null;

        JPrimitiveObjectArray* JInetAddress::getSerialPersistentFields(){
            if (serialPersistentFields==null){
                serialPersistentFields=new JPrimitiveObjectArray(JObjectStreamField::getClazz(),3);
                serialPersistentFields->set(0,new JObjectStreamField(new JString("hostName"), JString::getClazz()));
                serialPersistentFields->set(1,new JObjectStreamField(new JString("address"), JPrimitiveInt::getClazz()));
        		serialPersistentFields->set(2,new JObjectStreamField(new JString("family"), JPrimitiveInt::getClazz()));
            }
            return serialPersistentFields;
        }

		void JInetAddress::readObject(JObjectInputStream* in){
        	JObjectInputStream::JGetField* gf = in->readFields();
        	hostName = dynamic_cast<JString*>(gf->get(new JString("hostName"), (JString*)null));
        	address->set(gf->get(new JString("address"), (jint)0));
        	family->set(gf->get(new JString("family"), (jint)0));
    	}

    	void JInetAddress::writeObject(JObjectOutputStream* out){
        	JObjectOutputStream::JPutField* pf = out->putFields();
	        pf->put(new JString("hostName"), getHostName());
	        pf->put(new JString("address"), address->get());
	        pf->put(new JString("family"), family->get());
	        out->writeFields();
	    }

		JInetAddress::~JInetAddress() {
		}

	}
}
