#ifndef JCPP_NATIVE_UNIXOS_NET_UNIXSOCKET
#define JCPP_NATIVE_UNIXOS_NET_UNIXSOCKET

#include "jcpp/native/api/net/NativeSocket.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"
#include "jcpp/native/unixos/net/UnixSocketOutputStream.h"
#include "jcpp/native/unixos/net/UnixSocketInputStream.h"

using namespace jcpp::native::api::net;
using namespace jcpp::native::api;
using namespace jcpp::native::unixos::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				class JCPP_EXPORT UnixSocket: public NativeSocket {

				private:
					static NativeString className;

					UnixMutex mutex;

					jbool bound;
					jbool closed;
					jbool connected;

					int socket;

					UnixSocketInputStream * inputStream;
					UnixSocketOutputStream * outputStream;

					UnixSocket(const UnixSocket&);
					UnixSocket& operator =(const UnixSocket&);

				public:
					UnixSocket();
					UnixSocket(int socket, const NativeInetSocketAddress& remoteSocketAddress, const NativeInetSocketAddress& localSocketAddress);

					virtual ~UnixSocket();

					virtual void bind(const NativeInetSocketAddress& localSocketAddress);
					virtual void connect(const NativeInetSocketAddress& remoteSocketAddress, jint timeout = 0);
					virtual void close();

					virtual NativeInputStream * getInputStream();
					virtual NativeOutputStream * getOutputStream();

					virtual void shutdownInput();
					virtual void shutdownOutput();

					virtual jbool isInputShutdown();
					virtual jbool isOutputShutdown();

					virtual jbool isBound();
					virtual jbool isClosed();
					virtual jbool isConnected();

					virtual void sendUrgentData(jbyte data);

					virtual jbool getKeepAlive();
					virtual void setKeepAlive(jbool on);
					virtual jbool getOOBInline();
					virtual void setOOBInline(jbool on);
					virtual jint getReceiveBufferSize();
					virtual void setReceiveBufferSize(jint size);

					virtual jbool getReuseAddress();
					virtual void setReuseAddress(jbool on);
					virtual jint getSendBufferSize();
					virtual void setSendBufferSize(jint size);
					virtual jint getSoLinger();
					virtual void setSoLinger(jbool on, jint linger);

					virtual jint getSoTimeout();
					virtual void setSoTimeout(jint timeout);
					virtual jbool getTcpNoDelay();
					virtual void setTcpNoDelay(jbool on);

				};

			}
		}
	}
}

#endif
