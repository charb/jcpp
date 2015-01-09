#ifndef JCPP_NET_JINETADDRESS_H
#define JCPP_NET_JINETADDRESS_H

#include "jcpp/io/JSerializable.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/native/api/net/NativeInetAddress.h"

using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::native::api::net;

namespace jcpp {

	namespace net {

		class JInetSocketAddress;
		class JServerSocket;
		class JSocket;
		class JInetAddressClass;
		class JInet4Address;

		/**
		 * TODO Implement:
		 * 		virtual jbool isReachable(jint timeout);
		 * 		virtual jbool isReachable(JNetworkInterface, jint ttl, jint timeout);
		 *
		 */

		//@Class(canonicalName="java.net.InetAddress", simpleName="InetAddress");
		class JCPP_EXPORT JInetAddress: public JObject, public JSerializable {

		private:
			static const jlong serialVersionUID = 3286316764910316507LL;

		protected:
			static jint IPv4;
			static jint IPv6;
			JString* hostName;
			JPrimitiveInt* address;
			JPrimitiveInt* family;

			JInetAddress();
			JInetAddress(JClass* _clazz, JPrimitiveInt* _family);
			virtual JString* getHostNameWithoutResolving();
			virtual NativeInetAddress createNativeInetAddress();

			static JInetAddress* createInetAddress(const NativeInetAddress& nativeInetAddress);
			static JInetAddress* anyLocalAddress();
			static jbool isIPv4MappedAddress(JPrimitiveByteArray* addr);
			static JPrimitiveByteArray* convertFromIPv4MappedAddress(JPrimitiveByteArray* addr);
			virtual JObject* readResolve();
			static JPrimitiveObjectArray* serialPersistentFields;
            static JPrimitiveObjectArray* getSerialPersistentFields();
			virtual void readObject(JObjectInputStream* s);
			virtual void writeObject(JObjectOutputStream* s);

		public:
			static JClass* getClazz();

			static JInetAddress* getByAddress(JString* host, JPrimitiveByteArray* addr);

			static JInetAddress* getByName(JString* host);

			static JPrimitiveObjectArray* getAllByName(JString* host); // Array of JInetAddress

			static JInetAddress* getLoopbackAddress();

			static JInetAddress* getByAddress(JPrimitiveByteArray* addr);

			static JInetAddress* getLocalHost();

			virtual jbool isMulticastAddress();

			virtual jbool isAnyLocalAddress();

			virtual jbool isLoopbackAddress();

			virtual jbool isLinkLocalAddress();

			virtual jbool isSiteLocalAddress();

			virtual jbool isMCGlobal();

			virtual jbool isMCNodeLocal();

			virtual jbool isMCLinkLocal();

			virtual jbool isMCSiteLocal();

			virtual jbool isMCOrgLocal();

			virtual JString* getHostName();

			virtual JPrimitiveByteArray* getAddress();

			virtual JString* getHostAddress();

			virtual jint hashCode();

			virtual jbool equals(JObject* o);

			virtual JString* toString();

			virtual ~JInetAddress();

			friend class JInetSocketAddress;
			friend class JServerSocket;
			friend class JSocket;
			friend class JInet4Address;

		};

	}

}

#endif
