#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/unixos/net/UnixServerSocket.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/api/nthread/ScopedLock.h"
#include "jcpp/native/unixos/net/UnixSocket.h"

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

using namespace jcpp::native::api;
using namespace jcpp::native::api::net;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				NativeString UnixServerSocket::className("jcpp::native::unixos::net::UnixServerSocket");

				UnixServerSocket::UnixServerSocket() :
						NativeServerSocket(), mutex(), timeout(0), bound(false), closed(false), socket(-1) {
				}

				UnixServerSocket::~UnixServerSocket() {
					close();
				}

				/**
				 * TODO Current implementation needs the socket address to be configured with a correct ip address (get localhost from net factory)
				 * Update implementation to us ANY_ADDR host name (user created InetAddress)
				 */
				void UnixServerSocket::bind(const NativeInetSocketAddress& _socketAddress, const jint backlog) {
					ScopedLock synchronize(mutex);

					if (isClosed()) {
						throw NativeException(className, "bind", SOCKET_EXCEPTION, "Server Socket is closed!");
					}
					if (isBound()) {
						throw NativeException(className, "bind", SOCKET_EXCEPTION, "Server Socket is already bound!");
					}
					socketAddress = _socketAddress;

					if(socket == -1) {
						socket = ::socket((socketAddress.getHost().getFamily() == IPV4_FAMILY ? AF_INET : AF_INET6), SOCK_STREAM, IPPROTO_TCP);
						if (socket == -1) {
							UnixUtils::handleLastSocketError(className, "UnixServerSocket", "Failed to Create a server socket!");
						}

						if(reuseAddressSet) {
							setReuseAddress(reuseAddress);
						}
						if(receiveBufferSizeSet) {
							setReceiveBufferSize(receiveBufferSize);
						}
					}

					NativeInetAddress address = socketAddress.getHost();

					if (address.getFamily() == IPV4_FAMILY) {
						jbyte addressBuf[4];
						address.getAddress(addressBuf);

						struct sockaddr_in sa;
						memset(&sa, 0, sizeof(sa));

						sa.sin_family = AF_INET;
						sa.sin_port = htons(socketAddress.getPort());
						memcpy(&sa.sin_addr, addressBuf, 4);

						if (::bind(socket, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
							UnixUtils::handleLastSocketError(className, "bind", "Failed to Bind the Server Socket to the socket inet address!");
						}

						socklen_t nameLength = (socklen_t) sizeof(sa);
						if (getsockname(socket, (struct sockaddr *) &sa, &nameLength) == -1) {
							UnixUtils::handleLastSocketError(className, "bind", "Failed to get socket name information after binding to the socket inet address!");
						}
						socketAddress = NativeInetSocketAddress(socketAddress.getHost(), ntohs(sa.sin_port));
					} else {
						jbyte addressBuf[16];
						address.getAddress(addressBuf);

						struct sockaddr_in6 sa;
						memset(&sa, 0, sizeof(sa));

						sa.sin6_family = AF_INET6;
						sa.sin6_port = htons(socketAddress.getPort());
						memcpy(&sa.sin6_addr, addressBuf, 16);

						if (::bind(socket, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
							UnixUtils::handleLastSocketError(className, "bind", "Failed to Bind the Server Socket to the socket inet address!");
						}

						socklen_t nameLength = (socklen_t) sizeof(sa);
						if (getsockname(socket, (struct sockaddr *) &sa, &nameLength) == -1) {
							UnixUtils::handleLastSocketError(className, "bind", "Failed to get socket name information after binding to the socket inet address!");
						}
						socketAddress = NativeInetSocketAddress(socketAddress.getHost(), ntohs(sa.sin6_port));
					}
					if (listen(socket, backlog < 1 ? 50 : backlog) == -1) {
						UnixUtils::handleLastSocketError(className, "bind", "Failed to Listen on the Server Socket!");
					}
					bound = true;
				}

				NativeSocket * UnixServerSocket::accept() {
					if (isClosed()) {
						throw NativeException(className, "accept", SOCKET_EXCEPTION, "Server Socket is closed");
					}
					if (!isBound()) {
						throw NativeException(className, "accept", SOCKET_EXCEPTION, "Server Socket is not bound yet");
					}

					jbyte address[16];
					char hostname[NI_MAXHOST + 1];
					char ipstringbuffer[INET6_ADDRSTRLEN];

					if (timeout > 0) {
						jlong selectTimeout = timeout;
						while (true) {
							fd_set acceptSet;
							FD_ZERO(&acceptSet);
							FD_SET(socket, &acceptSet);

							struct timeval tv;
							UnixUtils::longToTimeval(tv, (jlong) selectTimeout);

							jlong startTime = UnixUtils::getCurrentTimeMillis();
							int selectResult = select(FD_SETSIZE, &acceptSet, NULL, NULL, &tv);
							jlong endTime = UnixUtils::getCurrentTimeMillis();

							if (selectResult == 0) {
								throw NativeException(className, "accept", SOCKET_TIMEOUT_EXCEPTION, "Failed to Accept a socket with the specified timeout");
							} else if (selectResult == -1) {
								if (errno == EINTR) {
									selectTimeout -= (endTime - startTime);
									if (selectTimeout <= 0) {
										throw NativeException(className, "accept", SOCKET_TIMEOUT_EXCEPTION, "Failed to Accept a socket with the specified timeout");
									}
									continue;
								}
								UnixUtils::handleLastSocketError(className, "accept", "Failed to call select to wait for accept timeout!");
							}
							if (!FD_ISSET(socket, &acceptSet)) {
								throw NativeException(className, "accept", SYSTEM_EXCEPTION, "Select method returned normally without the server socket being set in the accepted fd set!");
							}
							break;
						}
					}

					int clientSocket = -1;

					if (socketAddress.getHost().getFamily() == IPV4_FAMILY) {
						struct sockaddr_in sa;
						memset(&sa, 0, sizeof(sa));
						socklen_t nameLength = (socklen_t) sizeof(sa);

						EINTR_RETRY_R(clientSocket, ::accept(socket, (struct sockaddr * ) &sa, &nameLength))

						if (clientSocket == -1) {
							throw NativeException(className, "bind", SOCKET_EXCEPTION, "Server Socket is not bound yet");
						}

						memcpy(address, &sa.sin_addr, 4);
						if (getnameinfo((struct sockaddr *) &sa, sizeof(struct sockaddr_in), hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD) != 0) {
							UnixUtils::handleLastSocketError(className, "accept", "Failed to call getnameinfo to get host name from IPv4 address!");
						}
						inet_ntop(AF_INET, &sa.sin_addr, ipstringbuffer, INET6_ADDRSTRLEN);

						return new UnixSocket(clientSocket, NativeInetSocketAddress(NativeInetAddress(NativeString(hostname), NativeString(ipstringbuffer), IPV4_FAMILY, (jbyte *) address), ntohs(sa.sin_port)), socketAddress);

					} else {
						struct sockaddr_in6 sa;
						memset(&sa, 0, sizeof(sa));
						socklen_t nameLength = (socklen_t) sizeof(sa);

						EINTR_RETRY_R(clientSocket, ::accept(socket, (struct sockaddr * ) &sa, &nameLength))

						if (clientSocket == -1) {
							throw NativeException(className, "bind", SOCKET_EXCEPTION, "Server Socket is not bound yet");
						}

						memcpy(address, &sa.sin6_addr, 16);
						if (getnameinfo((struct sockaddr *) &sa, sizeof(struct sockaddr_in6), hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD) != 0) {
							UnixUtils::handleLastSocketError(className, "accept", "Failed to call getnameinfo to get host name from IPv6 address!");
						}
						inet_ntop(AF_INET6, (const void *) &sa.sin6_addr, ipstringbuffer, INET6_ADDRSTRLEN);

						return new UnixSocket(clientSocket, NativeInetSocketAddress(NativeInetAddress(NativeString(hostname), NativeString(ipstringbuffer), IPV6_FAMILY, (jbyte *) address), ntohs(sa.sin6_port)), socketAddress);
					}
				}

				void UnixServerSocket::close() {
					ScopedLock synchronize(mutex);
					if (closed) {
						return;
					}

					EINTR_RETRY(::close(socket))

					if (result == -1) {
						UnixUtils::handleLastSocketError(className, "close", "Failed to close the socket!");
					}
					closed = true;
				}

				jbool UnixServerSocket::isBound() {
					ScopedLock synchronize(mutex);
					return bound;
				}

				jbool UnixServerSocket::isClosed() {
					ScopedLock synchronize(mutex);
					return closed;
				}

				jint UnixServerSocket::getReceiveBufferSize() {
					if(socket == -1) {
						return reuseAddress;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getReceiveBufferSize", SOCKET_EXCEPTION, "Server Socket is closed");
						}
						int optValue = 0;
						socklen_t optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_RCVBUF, (char *) &optValue, &optlen) == -1) {
							UnixUtils::handleLastSocketError(className, "getReceiveBufferSize", "Failed to call get socket option!");
						}
						return optValue;
					}
				}

				void UnixServerSocket::setReceiveBufferSize(jint size) {
					if(socket == -1) {
						receiveBufferSizeSet = true;
						receiveBufferSize = size;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setReceiveBufferSize", SOCKET_EXCEPTION, "Server Socket is closed");
						}
						int optValue = size;
						if (setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (const char *) &optValue, sizeof(int)) == -1) {
							UnixUtils::handleLastSocketError(className, "setReceiveBufferSize", "Failed to call set socket option!");
						}
					}
				}

				jbool UnixServerSocket::getReuseAddress() {
					if(socket == -1) {
						return reuseAddress;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getReuseAddress", SOCKET_EXCEPTION, "Server Socket is closed");
						}
						int optValue = 0;
						socklen_t optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *) &optValue, &optlen) == -1) {
							UnixUtils::handleLastSocketError(className, "getReuseAddress", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void UnixServerSocket::setReuseAddress(jbool on) {
					if(socket == -1) {
						reuseAddressSet = true;
						reuseAddress = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setReuseAddress", SOCKET_EXCEPTION, "Server Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &optValue, sizeof(int)) == -1) {
							UnixUtils::handleLastSocketError(className, "setReuseAddress", "Failed to call set socket option!");
						}
					}
				}

				jint UnixServerSocket::getSoTimeout() {
					if (isClosed()) {
						throw NativeException(className, "getSoTimeout", SOCKET_EXCEPTION, "Server Socket is closed");
					}
					return timeout;
				}

				void UnixServerSocket::setSoTimeout(jint timeoutValue) {
					if (isClosed()) {
						throw NativeException(className, "setSoTimeout", SOCKET_EXCEPTION, "Server Socket is closed");
					}
					if (timeoutValue < 0) {
						throw NativeException(className, "setSoTimeout", ILLEGAL_ARGUMENT_EXCEPTION, "Invalid negative socket timeout value!");
					}
					timeout = timeoutValue;
				}
			}
		}
	}
}
