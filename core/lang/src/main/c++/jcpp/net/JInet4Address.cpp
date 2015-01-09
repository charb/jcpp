#include "jcpp/net/JInet4Address.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::native::api;
using namespace jcpp::lang;

namespace jcpp {
	namespace net {

		JInet4Address::JInet4Address() : JInetAddress(getClazz(), new JPrimitiveInt(IPv4)) {
		}

		JInet4Address::JInet4Address(JString* _hostName, JPrimitiveByteArray* addr) : JInetAddress(getClazz(), new JPrimitiveInt(IPv4)) {
			hostName = _hostName;
			if (addr != null) {
				if (addr->size() == 4) {
					jint a  = addr->getByte(3) & 0xFF;
					a |= ((addr->getByte(2) << 8) & 0xFF00);
					a |= ((addr->getByte(1) << 16) & 0xFF0000);
					a |= ((addr->getByte(0) << 24) & 0xFF000000);
					address->set(a);
				}
			}
		}

		JInet4Address::JInet4Address(JString* _hostName, jint addr) : JInetAddress(getClazz(), new JPrimitiveInt(IPv4)) {
			hostName = _hostName;
			address->set(addr);
		}

		JObject* JInet4Address::writeReplace(){
        	JInetAddress* inet = new JInetAddress();
	        inet->hostName = hostName;
	        inet->address = address;
        	inet->family->set(2);
	        return inet;
	    }

		jbool JInet4Address::isMulticastAddress() {
			return (address->get() & 0xf0000000) == 0xe0000000;
		}

		jbool JInet4Address::isAnyLocalAddress() {
			return address->get() == 0;
		}

		jbool JInet4Address::isLoopbackAddress() {
			return getAddress()->getByte(0) == 127;
		}

		jbool JInet4Address::isLinkLocalAddress() {
			unsigned int add = (unsigned int) address->get();
			return (((add >> 24) & 0xFF) == 169) && (((add >> 16) & 0xFF) == 254);
		}

		jbool JInet4Address::isSiteLocalAddress() {
			unsigned int add = (unsigned int) address->get();
	        return (((add >> 24) & 0xFF) == 10)
	            || ((((add >> 24) & 0xFF) == 172)
	                && (((add >> 16) & 0xF0) == 16))
	            || ((((add >> 24) & 0xFF) == 192)
	                && (((add >> 16) & 0xFF) == 168));
		}

		jbool JInet4Address::isMCGlobal() {
			JPrimitiveByteArray* byteAddr = getAddress();
	        return ((byteAddr->getByte(0) & 0xff) >= 224 && (byteAddr->getByte(0) & 0xff) <= 238 ) &&
	            !((byteAddr->getByte(0) & 0xff) == 224 && byteAddr->getByte(1) == 0 &&
	              byteAddr->getByte(2) == 0);
		}

		jbool JInet4Address::isMCNodeLocal() {
			return false;
		}

		jbool JInet4Address::isMCLinkLocal() {
			unsigned int add = (unsigned int) address->get();
			return (((add >> 24) & 0xFF) == 224)
					&& (((add >> 16) & 0xFF) == 0)
			        && (((add >> 8) & 0xFF) == 0);
		}

		jbool JInet4Address::isMCSiteLocal() {
			unsigned int add = (unsigned int) address->get();
			return (((add >> 24) & 0xFF) == 239)
					&& (((add >> 16) & 0xFF) == 255);
		}

		jbool JInet4Address::isMCOrgLocal() {
			unsigned int add = (unsigned int) address->get();
			return (((add >> 24) & 0xFF) == 239)
				&& (((add >> 16) & 0xFF) >= 192)
				&& (((add >> 16) & 0xFF) <= 195);
		}

		JPrimitiveByteArray* JInet4Address::getAddress() {
			JPrimitiveByteArray* addr = new JPrimitiveByteArray(4);

			unsigned int ua = (unsigned int)address->get();

			addr->setByte(0, (jbyte) ((ua >> 24) & 0xFF));
			addr->setByte(1, (jbyte) ((ua >> 16) & 0xFF));
			addr->setByte(2, (jbyte) ((ua >> 8) & 0xFF));
			addr->setByte(3, (jbyte) (ua & 0xFF));

			return addr;
		}

		JString* JInet4Address::getHostAddress() {
			JPrimitiveByteArray* src = getAddress();
			JStringBuilder* sb = new JStringBuilder();
			return sb->append(src->getByte(0) & 0xff)->append(".")->append(src->getByte(1) & 0xff)->append(".")->append(src->getByte(2) & 0xff)->append(".")->append(src->getByte(3) & 0xff)->toString();
		}

		jint JInet4Address::hashCode() {
			return address->get();
		}

		jbool JInet4Address::equals(JObject* obj) {
			if ((obj == null) || obj->getClass()!=getClazz()){
				return false;
			}
			JInet4Address* other = dynamic_cast<JInet4Address*>(obj);
			return address->equals(other->address);
		}

		JInet4Address::~JInet4Address() {
		}

	}
}
