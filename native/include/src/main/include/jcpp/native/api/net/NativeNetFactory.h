#ifndef JCPP_NATIVE_API_NET_NATIVENETFACTORY
#define JCPP_NATIVE_API_NET_NATIVENETFACTORY

#include <vector>
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/api/net/NativeInetAddress.h"
#include "jcpp/native/api/net/NativeSelector.h"
#include "jcpp/native/api/net/NativeSocket.h"
#include "jcpp/native/api/net/NativeServerSocket.h"

namespace jcpp {
	namespace native {
		namespace api {
			class NativeFactory;
		}
	}
}

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				class JCPP_EXPORT NativeNetFactory {

					friend class jcpp::native::api::NativeFactory;

				private:
					static NativeNetFactory * instance;

				protected:
					NativeNetFactory();

					static NativeNetFactory * getInstance();
					static void setInstance(NativeNetFactory * instance);

				public:
					virtual ~NativeNetFactory();

					//~-------------------------------------------------------------------------------------------
					//~ NativeInetAddress Factory Methods
					//~-------------------------------------------------------------------------------------------

					/**
					 * Determines the IP address of a host, given the host's name (first found starting with IPv4)
					 * The host name can either be a machine name, such as "www.google.com", or a textual representation of its IP address.
					 * If the host is empty then a NativeInetAddress representing an address of the loopback interface is returned.
					 */
					virtual NativeInetAddress getInetAddressByName(const NativeString& host) = 0;
					/**
					 * Given the name of a host, fills a vector with its IP addresses, based on the configured name service on the system.
					 * The host name can either be a machine name, such as "www.google.com", or a textual representation of its IP address.
					 * If the host is empty then a NativeInetAddress representing an address of the loopback interface is returned.
					 */
					virtual void getAllInetAddressesByName(std::vector<NativeInetAddress>& addresses, const NativeString& host) = 0;
					/**
					 * Returns an InetAddress object given the raw IP address. The argument is in network byte order: the highest order byte of the address is in getAddress()[0].
					 * IPv4 address byte array must be 4 bytes long and IPv6 byte array must be 16 bytes long
					 */
					virtual NativeInetAddress getInetAddressByAddress(const jbyte * address, const InetAddressFamily family) = 0;
					/**
					 * Returns the address of the local host (first found starting with IPv4)
					 */
					virtual NativeInetAddress getLocalHost() = 0;
					/**
					 * Returns all the addresses of the local host.
					 */
					virtual void getAllInetAddressesForLocalHost(std::vector<NativeInetAddress>& addresses) = 0;
					/**
					 * Returns the loopback address.
					 */
					virtual NativeInetAddress getLoopbackAddress() = 0;

					//~-------------------------------------------------------------------------------------------
					//~ NativeServerSocket Factory Methods
					//~-------------------------------------------------------------------------------------------

					virtual NativeServerSocket * createNativeServerSocket() = 0;

					//~-------------------------------------------------------------------------------------------
					//~ NativeSocket Factory Methods
					//~-------------------------------------------------------------------------------------------

					virtual NativeSocket * createNativeSocket() = 0;

					//~-------------------------------------------------------------------------------------------
					//~ NativeSelector Factory Methods
					//~-------------------------------------------------------------------------------------------

				};

			}
		}
	}
}

#endif
