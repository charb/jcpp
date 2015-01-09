#include "jcpp/native/unixos/net/UnixNetFactory.h"
#include "jcpp/native/api/NativeException.h"

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				NativeString UnixNetFactory::className("jcpp::native::unixos::net::UnixNetFactory");

				UnixNetFactory::UnixNetFactory() {
				}

				UnixNetFactory::~UnixNetFactory() {
				}

				NativeInetAddress UnixNetFactory::getInetAddressByName(const NativeString& host) {
					std::vector<NativeInetAddress> addresses;
					getAllInetAddressesByName(addresses, host);

					if (addresses.size() == 0) {
						throw NativeException(className, "getInetAddressByName", UNKNOWN_HOST_EXCEPTION, "Failed to get Address Info for host: " + host);
					}
					return addresses[0];
				}

				void UnixNetFactory::getAllInetAddressesByName(std::vector<NativeInetAddress>& addresses, const NativeString& host) {
					jbyte address[16];
					if (inet_pton(AF_INET, host.getString().c_str(), address)) {
						addresses.push_back(getInetAddressByAddress(address, IPV4_FAMILY));
					} else if (inet_pton(AF_INET6, host.getString().c_str(), address)) {
						addresses.push_back(getInetAddressByAddress(address, IPV6_FAMILY));
					} else {

						std::vector<NativeInetAddress> ipv4Addresses;
						std::vector<NativeInetAddress> ipv6Addresses;

						struct addrinfo * result = NULL;
						struct addrinfo *ptr = NULL;
						struct addrinfo hints;

						memset(&hints, 0, sizeof(hints));
						hints.ai_flags = AI_CANONNAME;
						hints.ai_family = AF_UNSPEC;
						hints.ai_socktype = SOCK_STREAM;
						hints.ai_protocol = IPPROTO_TCP;

						int errorCode = 0;
						if ((errorCode = getaddrinfo(host.getString().c_str(), NULL, &hints, &result)) != 0) {
							checkErrorCode(errorCode, className, "getAllInetAddressesByName", "Failed to get Address Info!");
						}

						NativeString hostName = result->ai_canonname;
						InetAddressFamily family = IPV4_FAMILY;

						char ipstringbuffer[INET6_ADDRSTRLEN];
						for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
							if (ptr->ai_family == AF_INET) {
								family = IPV4_FAMILY;
								memcpy(address, &((struct sockaddr_in *) ptr->ai_addr)->sin_addr, 4);
								inet_ntop(ptr->ai_family, (const void *) address, ipstringbuffer, INET6_ADDRSTRLEN);
								ipv4Addresses.push_back(NativeInetAddress(hostName, NativeString(ipstringbuffer), family, address));
							} else if (ptr->ai_family == AF_INET6) {
								family = IPV6_FAMILY;
								memcpy(address, &((struct sockaddr_in6 *) ptr->ai_addr)->sin6_addr, 16);
								inet_ntop(ptr->ai_family, (const void *) address, ipstringbuffer, INET6_ADDRSTRLEN);
								ipv6Addresses.push_back(NativeInetAddress(hostName, NativeString(ipstringbuffer), family, address));
							}
						}

						for (std::vector<NativeInetAddress>::iterator it = ipv4Addresses.begin(); it != ipv4Addresses.end(); ++it) {
							addresses.push_back(*it);
						}
						for (std::vector<NativeInetAddress>::iterator it = ipv6Addresses.begin(); it != ipv6Addresses.end(); ++it) {
							addresses.push_back(*it);
						}

						freeaddrinfo(result);
					}
				}

				NativeInetAddress UnixNetFactory::getInetAddressByAddress(const jbyte * address, const InetAddressFamily family) {
					char hostname[NI_MAXHOST + 1];

					char ipstringbuffer[INET6_ADDRSTRLEN];
					int errorCode = 0;

					if (family == IPV4_FAMILY) {
						struct sockaddr_in sa;
						memset(&sa, 0, sizeof(sa));
						sa.sin_family = AF_INET;
						memcpy(&sa.sin_addr, address, 4);

						if ((errorCode = getnameinfo((struct sockaddr *) &sa, sizeof(struct sockaddr_in), hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD)) != 0) {
							checkErrorCode(errorCode, className, "getInetAddressByAddress", "Failed to get Name Info!");
						}
						inet_ntop(AF_INET, (const void *) &sa.sin_addr, ipstringbuffer, INET6_ADDRSTRLEN);
						return NativeInetAddress(NativeString(hostname), NativeString(ipstringbuffer), family, address);
					} else {
						struct sockaddr_in6 sa;
						memset(&sa, 0, sizeof(sa));
						sa.sin6_family = AF_INET6;
						memcpy(&sa.sin6_addr, address, 16);

						if ((errorCode = getnameinfo((struct sockaddr *) &sa, sizeof(struct sockaddr_in6), hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD)) != 0) {
							checkErrorCode(errorCode, className, "getInetAddressByAddress", "Failed to get Name Info!");
						}
						inet_ntop(AF_INET6, (const void *) &sa.sin6_addr, ipstringbuffer, INET6_ADDRSTRLEN);
						return NativeInetAddress(NativeString(hostname), NativeString(ipstringbuffer), family, address);
					}
				}

				NativeInetAddress UnixNetFactory::getLocalHost() {
					char hostname[NI_MAXHOST + 1];
					gethostname(hostname, NI_MAXHOST + 1);
					NativeString localhost(hostname);
					return getInetAddressByName(localhost);
				}

				void UnixNetFactory::getAllInetAddressesForLocalHost(std::vector<NativeInetAddress>& addresses) {
					char hostname[NI_MAXHOST + 1];
					gethostname(hostname, NI_MAXHOST + 1);
					NativeString localhost(hostname);
					getAllInetAddressesByName(addresses, localhost);
				}

				NativeInetAddress UnixNetFactory::getLoopbackAddress() {
					NativeString loopbackAddress("localhost");
					return getInetAddressByName(loopbackAddress);
				}

				NativeServerSocket * UnixNetFactory::createNativeServerSocket() {
					return new UnixServerSocket();
				}

				NativeSocket * UnixNetFactory::createNativeSocket() {
					return new UnixSocket();
				}

				void UnixNetFactory::checkErrorCode(const int errorCode, const NativeString& className, const NativeString& methodName, const NativeString& message) {
					switch (errorCode) {
						case EAI_ADDRFAMILY:
							throw NativeException(className, methodName, UNKNOWN_HOST_EXCEPTION, "The specified network host does not have any network addresses: " + message, errorCode);
						case EAI_AGAIN:
							throw NativeException(className, methodName, PROTOCOL_EXCEPTION, "Nonauthoritative host not found: " + message, errorCode);
						case EAI_FAIL:
							throw NativeException(className, methodName, PROTOCOL_EXCEPTION, "The name server returned a permanent failure indication.: " + message, errorCode);
						case EAI_MEMORY:
							throw NativeException(className, methodName, OUT_OF_MEMORY_EXCEPTION, "Insufficient memory available: " + message, errorCode);
						case EAI_NODATA:
							throw NativeException(className, methodName, UNKNOWN_HOST_EXCEPTION, "The specified network host exists, but does not have any network addresses defined: " + message, errorCode);
						default:
							throw NativeException(className, methodName, SOCKET_EXCEPTION, message, errorCode);
					}
				}
			}
		}
	}
}
