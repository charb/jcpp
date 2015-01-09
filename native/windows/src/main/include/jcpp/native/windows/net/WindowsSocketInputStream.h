#ifndef JCPP_NATIVE_WINDOWS_NET_WINDOWSSSOCKETINPUTSTREAM
#define JCPP_NATIVE_WINDOWS_NET_WINDOWSSSOCKETINPUTSTREAM

#include "jcpp/native/api/io/NativeInputStream.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/windows/WindowsUtils.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace net {

				class WindowsSocket;

				class JCPP_EXPORT WindowsSocketInputStream: public NativeInputStream {

					friend class WindowsSocket;

				private:
					static NativeString className;

					SOCKET socket;
					jbool eof;
					jint timeout;

					volatile jbool streamClosed;
					volatile jbool socketClosed;

					WindowsSocketInputStream(const WindowsSocketInputStream&);
					WindowsSocketInputStream& operator =(const WindowsSocketInputStream&);

					void markSocketClosed();

				public:
					WindowsSocketInputStream(SOCKET socket);
					virtual ~WindowsSocketInputStream();

					virtual jbyte read();
					virtual jint read(jbyte * buf, jint offset, jint length);
					virtual jlong skip(jlong offset);
					virtual jlong available();
					virtual void close();

					jbool isStreamClosed();
					jint getSoTimeout();
					void setSoTimeout(jint timeout);

				};

			}
		}
	}
}

#endif
