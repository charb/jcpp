#ifndef JCPP_NATIVE_WINDOWS_NET_WINDOWSSOCKETOUTPUTSTREAM
#define JCPP_NATIVE_WINDOWS_NET_WINDOWSSOCKETOUTPUTSTREAM

#include "jcpp/native/api/io/NativeOutputStream.h"
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

				class JCPP_EXPORT WindowsSocketOutputStream: public NativeOutputStream {

					friend class WindowsSocket;

				private:
					static NativeString className;

					SOCKET socket;

					volatile jbool streamClosed;
					volatile jbool socketClosed;

					WindowsSocketOutputStream(const WindowsSocketOutputStream&);
					WindowsSocketOutputStream& operator =(const WindowsSocketOutputStream&);

					void markSocketClosed();

				public:
					WindowsSocketOutputStream(SOCKET socket);
					virtual ~WindowsSocketOutputStream();

					virtual void write(jbyte byte);
					virtual void write(jbyte * buf, jint offset, jint length);
					virtual void flush();
					virtual void close();

					jbool isStreamClosed();

				};

			}
		}
	}

}

#endif
