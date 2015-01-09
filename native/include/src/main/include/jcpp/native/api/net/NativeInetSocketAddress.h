#ifndef JCPP_NATIVE_API_NET_NATIVEINETSOCKETADDRESS
#define JCPP_NATIVE_API_NET_NATIVEINETSOCKETADDRESS

#include "jcpp/native/api/net/NativeInetAddress.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {


				class JCPP_EXPORT NativeInetSocketAddress {

				private:
					NativeInetAddress host;
					jint port;

				public:
					NativeInetSocketAddress();
					NativeInetSocketAddress(const NativeInetAddress& host, const jint port);
					NativeInetSocketAddress(const NativeInetSocketAddress& socketAddress);
					virtual ~NativeInetSocketAddress();

					NativeInetAddress getHost() const;

					jint getPort() const;

				};

			}
		}
	}
}

#endif
