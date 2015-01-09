#ifndef JCPP_NATIVE_UNIXOS_NET_UNIXNETFACTORY
#define JCPP_NATIVE_UNIXOS_NET_UNIXNETFACTORY

#include "jcpp/native/api/net/NativeNetFactory.h"
#include "jcpp/native/unixos/net/UnixSocket.h"
#include "jcpp/native/unixos/net/UnixServerSocket.h"
#include "jcpp/native/unixos/net/UnixSelector.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::net;


namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				class JCPP_EXPORT UnixNetFactory: public NativeNetFactory {

				private:
					static NativeString className;

					void checkErrorCode(const int errorCode, const NativeString& className, const NativeString& methodName, const NativeString& message);

				public:
					UnixNetFactory();
					virtual ~UnixNetFactory();

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
