#include "jcpp/native/api/net/NativeInetAddress.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				NativeInetAddress::NativeInetAddress() : host(), hostAddress(), family(IPV4_FAMILY) {
					for (int i = 0; i < 16; i++) {
						address[i] = 0;
					}
				}

				NativeInetAddress::NativeInetAddress(const NativeString& host, const NativeString& hostAddress, const InetAddressFamily& family, const jbyte * addressArray) :
						host(host), hostAddress(hostAddress), family(family) {

					int addressLength = family == IPV4_FAMILY ? 4 : 16;
					for (int i = 0; i < addressLength; i++) {
						address[i] = addressArray[i];
					}
				}

				NativeInetAddress::NativeInetAddress(const NativeInetAddress& inetAddress) :
						host(inetAddress.host), hostAddress(inetAddress.hostAddress), family(inetAddress.family) {

					for (int i = 0; i < 16; i++) {
						address[i] = inetAddress.address[i];
					}
				}

				NativeInetAddress::~NativeInetAddress() {
				}

				void NativeInetAddress::getAddress(jbyte * addressBuffer) const {
					int addressLength = family == IPV4_FAMILY ? 4 : 16;
					for (int i = 0; i < addressLength; i++) {
						addressBuffer[i] = address[i];
					}
				}

				NativeString NativeInetAddress::getHostName() const {
					return host;
				}

				NativeString NativeInetAddress::getHostAddress() const {
					return hostAddress;
				}

				InetAddressFamily NativeInetAddress::getFamily() const {
					return family;
				}

			}
		}
	}
}
