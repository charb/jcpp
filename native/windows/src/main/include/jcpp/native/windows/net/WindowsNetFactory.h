#ifndef JCPP_NATIVE_WINDOWS_NET_WINDOWSNETFACTORY
#define JCPP_NATIVE_WINDOWS_NET_WINDOWSNETFACTORY

#include "jcpp/native/api/net/NativeNetFactory.h"
#include "jcpp/native/windows/net/WindowsSocket.h"
#include "jcpp/native/windows/net/WindowsServerSocket.h"
#include "jcpp/native/windows/net/WindowsSelector.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

using namespace jcpp::native::api;
using namespace jcpp::native::api::net;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace net {

				class JCPP_EXPORT WindowsNetFactory: public NativeNetFactory {

				private:
					static NativeString className;

					WSADATA wsaData;

				public:
					WindowsNetFactory();
					virtual ~WindowsNetFactory();

					virtual NativeInetAddress getInetAddressByName(const NativeString& host);
					virtual void getAllInetAddressesByName(std::vector<NativeInetAddress>& addresses, const NativeString& host);
					virtual NativeInetAddress getInetAddressByAddress(const jbyte * address, const InetAddressFamily family);
					virtual NativeInetAddress getLocalHost();
					virtual void getAllInetAddressesForLocalHost(std::vector<NativeInetAddress>& addresses);
					virtual NativeInetAddress getLoopbackAddress();

					virtual NativeServerSocket * createNativeServerSocket();
					virtual NativeSocket * createNativeSocket();

				};

			}
		}
	}
}

#endif
