#include "jcpp/native/api/net/NativeInetSocketAddress.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				NativeInetSocketAddress::NativeInetSocketAddress() : host(), port(0) {
				}

				NativeInetSocketAddress::NativeInetSocketAddress(const NativeInetAddress& host, const jint port) :
						host(host), port(port) {
				}

				NativeInetSocketAddress::NativeInetSocketAddress(const NativeInetSocketAddress& socketAddress) :
						host(socketAddress.host), port(socketAddress.port) {
				}

				NativeInetSocketAddress::~NativeInetSocketAddress() {

				}

				NativeInetAddress NativeInetSocketAddress::getHost() const {
					return host;
				}

				jint NativeInetSocketAddress::getPort() const {
					return port;
				}

			}
		}
	}
}

