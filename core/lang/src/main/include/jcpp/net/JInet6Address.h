#ifndef JCPP_NET_JINET6ADDRESS_H
#define JCPP_NET_JINET6ADDRESS_H

#include "jcpp/net/JInetAddress.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"

namespace jcpp {

	namespace net {

		/**
		 * TODO Implement:
		 * 		virtual jbool isReachable(jint timeout);
		 * 		virtual jbool isReachable(JNetworkInterface, jint ttl, jint timeout);
		 */

		//@Class(canonicalName="java.net.Inet6Address", simpleName="Inet6Address");
		class JCPP_EXPORT JInet6Address: public JInetAddress {

		private:
			static const jlong serialVersionUID = 6880410070516793377LL;

		protected:
			static jint INADDRSZ;
			JPrimitiveByteArray* ipaddress;
			jbool scope_id_set;
			jint scope_id;
			jbool scope_ifname_set;
			JString* ifname;

			JInet6Address();
			JInet6Address(JString* hostName, JPrimitiveByteArray* addr);

			static JPrimitiveObjectArray* serialPersistentFields;
            static JPrimitiveObjectArray* getSerialPersistentFields();
            virtual void readObject(JObjectInputStream* s);
			virtual void writeObject(JObjectOutputStream* s);

		public:
			static JClass* getClazz();

			virtual jbool isIPv4CompatibleAddress();

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

			virtual JPrimitiveByteArray* getAddress();

			virtual JString* getHostAddress();

			virtual jint hashCode();

			virtual jbool equals(JObject* o);

			virtual ~JInet6Address();

			friend class JInetAddress;
			friend class JInet6AddressClass;

		};

	}

}

#endif
