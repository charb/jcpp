#include "jcpp/native/api/net/NativeServerSocket.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				NativeServerSocket::NativeServerSocket() :
						socketAddress() {

					reuseAddressSet = false;
					reuseAddress = false;

					receiveBufferSizeSet = false;
					receiveBufferSize = 0;

				}

				NativeServerSocket::~NativeServerSocket() {
				}

				NativeInetSocketAddress NativeServerSocket::getLocalSocketAddress() const {
					return socketAddress;
				}

			}
		}
	}
}
