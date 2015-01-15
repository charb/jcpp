#ifndef JCPP_NET_JSOCKET_H
#define JCPP_NET_JSOCKET_H

#include "jcpp/lang/JObject.h"
#include "jcpp/net/JInetAddress.h"
#include "jcpp/net/JInetSocketAddress.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JOutputStream.h"
#include "jcpp/native/api/net/NativeSocket.h"

using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::native::api::net;

namespace jcpp {

	namespace net {
		class JServerSocket;

		//@Class(canonicalName="java.net.Socket", simpleName="Socket");
		class JCPP_EXPORT JSocket: public JObject {

		protected:

			// @IgnoreReflection()
			NativeSocket* nativeSocket;

			JInputStream* inputStream;
			JOutputStream* outputStream;

			JSocket(JClass* _class);

			// @IgnoreReflection()
			JSocket(NativeSocket* socket);

			// @IgnoreReflection()
			void init(JInetSocketAddress* address, JInetSocketAddress* localAddress, NativeSocket* nativeSocket);

		public:
			static JClass* getClazz();

			JSocket();

			JSocket(JString* host, jint port);
			JSocket(JInetAddress* address, jint port);
			JSocket(JString* host, jint port, JInetAddress* localAddr, jint localPort);
			JSocket(JInetAddress* address, jint port, JInetAddress* localAddr, jint localPort);

			virtual void connect(JSocketAddress* endpoint, jint timeout = 0);
			virtual void bind(JSocketAddress* bindpoint);
			virtual void close();

			virtual jbool isConnected();
			virtual jbool isBound();
			virtual jbool isClosed();

			virtual JInetAddress* getInetAddress();
			virtual JInetAddress* getLocalAddress();
			virtual jint getPort();
			virtual jint getLocalPort();
			virtual JSocketAddress* getRemoteSocketAddress();
			virtual JSocketAddress* getLocalSocketAddress();

			virtual JInputStream* getInputStream();
			virtual JOutputStream* getOutputStream();

			virtual void shutdownInput();
			virtual void shutdownOutput();

			virtual jbool isInputShutdown();
			virtual jbool isOutputShutdown();

			virtual void sendUrgentData (jint data);

			virtual void setTcpNoDelay(jbool on);
			virtual jbool getTcpNoDelay();

			virtual void setSoLinger(jbool on, jint linger);
			virtual jint getSoLinger();

			virtual void setOOBInline(jbool on);
			virtual jbool getOOBInline();

			virtual void setSoTimeout(jint timeout);
			virtual jint getSoTimeout();

			virtual void setSendBufferSize(jint size);
			virtual jint getSendBufferSize();

			virtual void setReceiveBufferSize(jint size);
			virtual jint getReceiveBufferSize();

			virtual void setKeepAlive(jbool on);
			virtual jbool getKeepAlive();

			virtual void setReuseAddress(jbool on);
			virtual jbool getReuseAddress();

			virtual JString* toString();

			virtual void finalize();

			virtual ~JSocket();

			friend class JServerSocket;
		};

	}

}

#endif
