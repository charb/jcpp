#ifndef JCPP_NATIVE_WINDOWS_NET_WINDOWSSOCKET
#define JCPP_NATIVE_WINDOWS_NET_WINDOWSSOCKET

#include "jcpp/native/api/net/NativeSocket.h"
#include "jcpp/native/windows/nthread/WindowsMutex.h"
#include "jcpp/native/windows/net/WindowsSocketOutputStream.h"
#include "jcpp/native/windows/net/WindowsSocketInputStream.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

using namespace jcpp::native::api::net;
using namespace jcpp::native::api;
using namespace jcpp::native::windows::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace net {
				class WindowsNetFactory;

				class JCPP_EXPORT WindowsSocket: public NativeSocket {

				private:
					static NativeString className;
					WindowsNetFactory* netFactory;

					WindowsMutex mutex;

					jbool bound;
					jbool closed;
					jbool connected;

					SOCKET socket;

					WindowsSocketInputStream * inputStream;
					WindowsSocketOutputStream * outputStream;

					WindowsSocket(const WindowsSocket&);
					WindowsSocket& operator =(const WindowsSocket&);

				public:
					WindowsSocket(WindowsNetFactory* netFactory);
					WindowsSocket(WindowsNetFactory* netFactory,SOCKET socket, const NativeInetSocketAddress& remoteSocketAddress, const NativeInetSocketAddress& localSocketAddress);
					virtual ~WindowsSocket();

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
