#ifndef JCPP_NET_JINET4ADDRESS_H
#define JCPP_NET_JINET4ADDRESS_H

#include "jcpp/net/JInetAddress.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

namespace jcpp {

	namespace net {

		/**
		 * TODO Implement:
		 * 		virtual jbool isReachable(jint timeout);
		 * 		virtual jbool isReachable(JNetworkInterface, jint ttl, jint timeout);
		 *
		 */

		//@Class(canonicalName="java.net.Inet4Address", simpleName="Inet4Address");
		class JCPP_EXPORT JInet4Address: public JInetAddress {

		private:
				static const jlong serialVersionUID = 3286316764910316507LL;

		protected:
			JInet4Address();
			JInet4Address(JString* hostName, JPrimitiveByteArray* addr);
			JInet4Address(JString* hostName, jint address);

			virtual JObject* writeReplace();

		public:
			static JClass* getClazz();

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

			virtual ~JInet4Address();

			friend class JInetAddress;
		};

	}

}

#endif
