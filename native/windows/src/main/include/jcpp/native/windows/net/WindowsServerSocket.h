#ifndef JCPP_NATIVE_WINDOWS_NET_WINDOWSSERVERSOCKET
#define JCPP_NATIVE_WINDOWS_NET_WINDOWSSERVERSOCKET

#include "jcpp/native/api/net/NativeServerSocket.h"
#include "jcpp/native/windows/nthread/WindowsMutex.h"

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

				class JCPP_EXPORT WindowsServerSocket: public NativeServerSocket {

				private:
					static NativeString className;

					WindowsNetFactory* netFactory;
					WindowsMutex mutex;

					jint timeout;
					jbool bound;
					jbool closed;

					SOCKET socket;

					WindowsServerSocket(const WindowsServerSocket&);
					WindowsServerSocket& operator =(const WindowsServerSocket&);

				public:

					WindowsServerSocket(WindowsNetFactory* netFactory);
					virtual ~WindowsServerSocket();

					virtual void bind(const NativeInetSocketAddress& socketAddress, const jint backlog = 50);
					virtual NativeSocket * accept();
					virtual void close();

					virtual jbool isBound();
					virtual jbool isClosed() ;

					virtual jint getReceiveBufferSize();
					virtual void setReceiveBufferSize(jint size);
					virtual jbool getReuseAddress();
					virtual void setReuseAddress(jbool on);
					virtual jint getSoTimeout();
					virtual void setSoTimeout(jint timeout);

				};

			}
		}
	}
}

#endif
