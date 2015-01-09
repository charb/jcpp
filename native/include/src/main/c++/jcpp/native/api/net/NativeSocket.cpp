#include "jcpp/native/api/net/NativeSocket.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				NativeSocket::NativeSocket() :
						remoteSocketAddress(), localSocketAddress() {

					keepAliveSet = false;
					keepAlive = false;

					oobInlineSet = false;
					oobInline = false;

					receiveBufferSizeSet = false;
					receiveBufferSize = 0;

					reuseAddressSet = false;
					reuseAddress = false;

					sendBufferSizeSet = false;
					sendBufferSize = 0;

					soLingerSet = false;
					soLingerOn = false;
					soLinger = 0;

					soTimeoutSet = false;
					soTimeout = 0;

					tcpNoDelaySet = false;
					tcpNoDelay = false;
				}

				NativeSocket::NativeSocket(const NativeInetSocketAddress& remoteSocketAddress, const NativeInetSocketAddress& localSocketAddress) :
						remoteSocketAddress(remoteSocketAddress), localSocketAddress(localSocketAddress) {

					keepAliveSet = false;
					keepAlive = false;

					oobInlineSet = false;
					oobInline = false;

					receiveBufferSizeSet = false;
					receiveBufferSize = 0;

					reuseAddressSet = false;
					reuseAddress = false;

					sendBufferSizeSet = false;
					sendBufferSize = 0;

					soLingerSet = false;
					soLingerOn = false;
					soLinger = 0;

					soTimeoutSet = false;
					soTimeout = 0;

					tcpNoDelaySet = false;
					tcpNoDelay = false;
				}

				NativeSocket::~NativeSocket() {

				}

				NativeInetSocketAddress NativeSocket::getRemoteSocketAddress() const {
					return remoteSocketAddress;
				}


				NativeInetSocketAddress NativeSocket::getLocalSocketAddress() const {
					return localSocketAddress;
				}

			}
		}
	}
}
