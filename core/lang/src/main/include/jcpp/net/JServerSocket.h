#ifndef JCPP_NET_JSERVERSOCKET_H
#define JCPP_NET_JSERVERSOCKET_H

#include "jcpp/lang/JObject.h"
#include "jcpp/net/JInetAddress.h"
#include "jcpp/net/JSocketAddress.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/native/api/net/NativeServerSocket.h"

using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::native::api::net;

namespace jcpp {

	namespace net {


		//@Class(canonicalName="java.net.ServerSocket", simpleName="ServerSocket");
		class JCPP_EXPORT JServerSocket: public JObject {

		protected:

			// @IgnoreReflection()
			NativeServerSocket* nativeServerSocket;

			JServerSocket(JClass* _class);
			JServerSocket(JClass* _class, jint port, jint backlog);
			JServerSocket(JClass* _class,jint port, jint backlog, JInetAddress* bindAddr);

			void init(jint port, jint backlog, JInetAddress* bindAddr, jbool bind);
		public:
			static JClass* getClazz();

			JServerSocket();
			JServerSocket(jint port);
			JServerSocket(jint port, jint backlog);
			JServerSocket(jint port, jint backlog, JInetAddress* bindAddr);

			virtual void bind(JSocketAddress* endpoint, jint backlog = 50);

			virtual JInetAddress* getInetAddress();
			virtual jint getLocalPort();
			virtual JSocketAddress* getLocalSocketAddress();

			virtual JSocket* accept();
			virtual void close();

			virtual jbool isBound();
			virtual jbool isClosed();

			virtual void setSoTimeout(jint timeout);
			virtual jint getSoTimeout();

			virtual void setReuseAddress(jbool on);
			virtual jbool getReuseAddress();

			virtual void setReceiveBufferSize (jint size);
			virtual jint getReceiveBufferSize();

			virtual JString* toString();

			virtual void finalize();

			virtual ~JServerSocket();
		};

	}

}

#endif
