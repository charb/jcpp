#ifndef JCPP_NATIVE_API_NET_NATIVEINETADDRESS
#define JCPP_NATIVE_API_NET_NATIVEINETADDRESS

#include "jcpp/native/api/NativeString.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				enum InetAddressFamily {
					IPV4_FAMILY, IPV6_FAMILY
				};

				class JCPP_EXPORT NativeInetAddress {

				private:
					jbyte address[16];
					NativeString host;
					NativeString hostAddress;
					InetAddressFamily family;

				public:
					NativeInetAddress();
					NativeInetAddress(const NativeString& host, const NativeString& hostAddress, const InetAddressFamily& family, const jbyte * address);
					NativeInetAddress(const NativeInetAddress& address);
					virtual ~NativeInetAddress();

					/**
					 * Returns the raw IP address of this InetAddress object.
					 * The result is in network byte order: the highest order byte of the address is in getAddress()[0].
					 * IPv4 address byte array must be 4 bytes long and IPv6 byte array must be 16 bytes long
					 */
					void getAddress(jbyte * addressBuffer) const;

					/**
					 * Gets the host name for this IP address.
					 */
					NativeString getHostName() const;

					/**
					 * Returns the IP address string in textual presentation.
					 */
					NativeString getHostAddress() const;

					/**
					 * Returns the Inet Address Family
					 */
					InetAddressFamily getFamily() const;
				};

			}
		}
	}
}

#endif
