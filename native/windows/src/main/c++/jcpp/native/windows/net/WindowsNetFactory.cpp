#include "jcpp/native/windows/net/WindowsNetFactory.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/windows/WindowsUtils.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace net {

				NativeString WindowsNetFactory::className("jcpp::native::windows::net::WindowsNetFactory");

				WindowsNetFactory::WindowsNetFactory() {
					int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
					if (iResult != 0) {
						throw NativeException(className, "WindowsNetFactory", SYSTEM_EXCEPTION, "Failed to initialized WinSock API, WSAStartup failed!");
					}
					if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
						WSACleanup();
						throw NativeException(className, "WindowsNetFactory", SYSTEM_EXCEPTION, "Could not find a usable version of Winsock.dll. Version found is not 2.2!");
					}
				}

				WindowsNetFactory::~WindowsNetFactory() {
					WSACleanup();
				}

				NativeInetAddress WindowsNetFactory::getInetAddressByName(const NativeString& host) {
					std::vector<NativeInetAddress> addresses;
					getAllInetAddressesByName(addresses, host);

					if (addresses.size() == 0) {
						throw NativeException(className, "getInetAddressByName", UNKNOWN_HOST_EXCEPTION, "Failed to get Address Info for host: " + host);
					}
					return addresses[0];
				}

				void WindowsNetFactory::getAllInetAddressesByName(std::vector<NativeInetAddress>& addresses, const NativeString& host) {
					jbyte address[16];
					if (inet_pton(AF_INET, host.getString().c_str(), address)) {
						addresses.push_back(getInetAddressByAddress(address, IPV4_FAMILY));
					} else if (inet_pton(AF_INET6, host.getString().c_str(), address)) {
						addresses.push_back(getInetAddressByAddress(address, IPV6_FAMILY));
					} else {

						std::vector<NativeInetAddress> ipv4Addresses;
						std::vector<NativeInetAddress> ipv6Addresses;

						struct addrinfo *result = NULL;
						struct addrinfo *ptr = NULL;
						struct addrinfo hints;

						ZeroMemory( &hints, sizeof(hints) );
						hints.ai_flags = AI_CANONNAME;
						hints.ai_family = AF_UNSPEC;
						hints.ai_socktype = SOCK_STREAM;
						hints.ai_protocol = IPPROTO_TCP;

						if (getaddrinfo(host.getString().c_str(), null, &hints, &result) != 0) {
							WindowsUtils::handleLastWinSockError(className, "getAllInetAddressesByName", "Failed to get Address Info!");
						}

						NativeString hostName = result->ai_canonname;
						InetAddressFamily family;

						memset(address, 0, 16);
						char ipstringbuffer[INET6_ADDRSTRLEN];
						DWORD length = INET6_ADDRSTRLEN;
						for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
							if (ptr->ai_family == AF_INET) {
								family = IPV4_FAMILY;
								memcpy(address, &((struct sockaddr_in *) ptr->ai_addr)->sin_addr, 4);
								inet_ntop(AF_INET, &((struct sockaddr_in *) ptr->ai_addr)->sin_addr, ipstringbuffer, INET6_ADDRSTRLEN);
								ipv4Addresses.push_back(NativeInetAddress(hostName, NativeString(ipstringbuffer), family, address));
							} else if (ptr->ai_family == AF_INET6) {
								family = IPV6_FAMILY;
								memcpy(address, &((struct sockaddr_in6 *) ptr->ai_addr)->sin6_addr, 16);
								/*TODO: review it with ADEL!!!!!!
								if (WSAAddressToString(ptr->ai_addr, sizeof(struct sockaddr_in6), NULL, ipstringbuffer, &length) != 0) {
									WindowsUtils::handleLastWinSockError(className, "getAllInetAddressesByName", "Failed to call WSAAddressToString for IPv6 address!");
								}*/
								if (WSAAddressToString(ptr->ai_addr, sizeof(struct sockaddr_in6), NULL, ipstringbuffer, &length) == 0) {
									ipv6Addresses.push_back(NativeInetAddress(hostName, NativeString(ipstringbuffer), family, address));
								}
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

				NativeInetAddress WindowsNetFactory::getInetAddressByAddress(const jbyte * address, const InetAddressFamily family) {
					char hostname[NI_MAXHOST + 1];

					char ipstringbuffer[INET6_ADDRSTRLEN];
					DWORD length = INET6_ADDRSTRLEN;
					if (family == IPV4_FAMILY) {
						struct sockaddr_in sa;
						ZeroMemory( &sa, sizeof(sa));
						sa.sin_family = AF_INET;
						memcpy(&sa.sin_addr, address, 4);

						if (getnameinfo((struct sockaddr *) &sa, sizeof(struct sockaddr_in), hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD) != 0) {
							WindowsUtils::handleLastWinSockError(className, "getInetAddressByAddress", "Failed to call getnameinfo to get host name from IPv4 address!");
						}
						inet_ntop(AF_INET, &sa.sin_addr, ipstringbuffer, INET6_ADDRSTRLEN);
						return NativeInetAddress(NativeString(hostname), NativeString(ipstringbuffer), family, (jbyte *) address);
					} else {
						struct sockaddr_in6 sa;
						ZeroMemory( &sa, sizeof(sa));
						sa.sin6_family = AF_INET6;
						memcpy(&sa.sin6_addr, address, 16);

						if (getnameinfo((struct sockaddr *) &sa, sizeof(struct sockaddr_in6), hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD) != 0) {
							WindowsUtils::handleLastWinSockError(className, "getInetAddressByAddress", "Failed to call getnameinfo to get host name from IPv6 address!");
						}
						if (WSAAddressToString((LPSOCKADDR) &sa, sizeof(struct sockaddr_in6), NULL, ipstringbuffer, &length) != 0) {
							WindowsUtils::handleLastWinSockError(className, "getInetAddressByAddress", "Failed to call WSAAddressToString for IPv6 address!");
						}
						return NativeInetAddress(NativeString(hostname), NativeString(ipstringbuffer), family, (jbyte *) address);
					}
				}

				NativeInetAddress WindowsNetFactory::getLocalHost() {
					NativeString localhost("");
					return getInetAddressByName(localhost);
				}

				void WindowsNetFactory::getAllInetAddressesForLocalHost(std::vector<NativeInetAddress>& addresses) {
					NativeString localhost("");
					getAllInetAddressesByName(addresses, localhost);
				}

				NativeInetAddress WindowsNetFactory::getLoopbackAddress() {
					NativeString loopbackAddress("localhost");
					return getInetAddressByName(loopbackAddress);
				}

				NativeServerSocket * WindowsNetFactory::createNativeServerSocket() {
					return new WindowsServerSocket(this);
				}

				NativeSocket * WindowsNetFactory::createNativeSocket() {
					return new WindowsSocket(this);
				}

			}
		}
	}
}
