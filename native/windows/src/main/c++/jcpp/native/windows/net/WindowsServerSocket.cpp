#include "jcpp/native/windows/WindowsUtils.h"
#include "jcpp/native/windows/net/WindowsServerSocket.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/api/nthread/ScopedLock.h"
#include "jcpp/native/windows/net/WindowsSocket.h"
#include "jcpp/native/windows/net/WindowsNetFactory.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::net;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace net {

				NativeString WindowsServerSocket::className("jcpp::native::windows::net::WindowsServerSocket");

				WindowsServerSocket::WindowsServerSocket(WindowsNetFactory* nf) :
						NativeServerSocket(), netFactory(nf), mutex(), bound(false), closed(false), socket(INVALID_SOCKET), timeout(0) {
				}

				WindowsServerSocket::~WindowsServerSocket() {
					close();
				}

				/**
				 * TODO Current implementation needs the socket address to be configured with a correct ip address (get localhost from net factory)
				 * Update implementation to us ANY_ADDR host name (user created InetAddress)
				 */
				void WindowsServerSocket::bind(const NativeInetSocketAddress& _socketAddress, const jint backlog) {
					ScopedLock synchronize(mutex);

					if (isClosed()) {
						throw NativeException(className, "bind", SOCKET_EXCEPTION, "Server Socket is closed!");
					}
					if (isBound()) {
						throw NativeException(className, "bind", SOCKET_EXCEPTION, "Server Socket is already bound!");
					}
					socketAddress = _socketAddress;

					if(socket == INVALID_SOCKET) {
						socket = ::socket((socketAddress.getHost().getFamily() == IPV4_FAMILY ? AF_INET : AF_INET6), SOCK_STREAM, IPPROTO_TCP);
						if (socket == INVALID_SOCKET) {
							WindowsUtils::handleLastWinSockError(className, "WindowsServerSocket", "Failed to Create a server socket!");
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
						ZeroMemory( &sa, sizeof(sa));

						sa.sin_family = AF_INET;
						sa.sin_port = htons(socketAddress.getPort());
						memcpy(&sa.sin_addr, addressBuf, 4);

						if (::bind(socket, (struct sockaddr *) &sa, sizeof(sa)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "bind", "Failed to Bind the Server Socket to the socket inet address!");
						}

						int nameLength = sizeof(sa);
						if (getsockname(socket, (struct sockaddr *) &sa, &nameLength) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "bind", "Failed to get socket name information after binding to the socket inet address!");
						}
						socketAddress = NativeInetSocketAddress(socketAddress.getHost(), ntohs(sa.sin_port));
					} else {
						jbyte addressBuf[16];
						address.getAddress(addressBuf);

						struct sockaddr_in6 sa;
						ZeroMemory( &sa, sizeof(sa));

						sa.sin6_family = AF_INET6;
						sa.sin6_port = htons(socketAddress.getPort());
						memcpy(&sa.sin6_addr, addressBuf, 16);

						if (::bind(socket, (struct sockaddr *) &sa, sizeof(sa)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "bind", "Failed to Bind the Server Socket to the socket inet address!");
						}

						int nameLength = sizeof(sa);
						if (getsockname(socket, (struct sockaddr *) &sa, &nameLength) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "bind", "Failed to get socket name information after binding to the socket inet address!");
						}
						socketAddress = NativeInetSocketAddress(socketAddress.getHost(), ntohs(sa.sin6_port));
					}
					if (listen(socket, backlog < 1 ? 50 : backlog) == SOCKET_ERROR) {
						WindowsUtils::handleLastWinSockError(className, "bind", "Failed to Listen on the Server Socket!");
					}
					bound = true;
				}

				NativeSocket * WindowsServerSocket::accept() {
					if (isClosed()) {
						throw NativeException(className, "accept", SOCKET_EXCEPTION, "Server Socket is closed");
					}
					if (!isBound()) {
						throw NativeException(className, "accept", SOCKET_EXCEPTION, "Server Socket is not bound yet");
					}

					jbyte address[16];
					char hostname[NI_MAXHOST + 1];
					char ipstringbuffer[INET6_ADDRSTRLEN];
					DWORD length = INET6_ADDRSTRLEN;

					if (timeout > 0) {
						fd_set acceptSet;
						FD_ZERO(&acceptSet);
						FD_SET(socket, &acceptSet);

						struct timeval tv;
						WindowsUtils::longToTimeval(tv, (jlong) timeout);

						int selectResult = select(0, &acceptSet, NULL, NULL, &tv);
						if (selectResult == 0) {
							throw NativeException(className, "accept", SOCKET_TIMEOUT_EXCEPTION, "Failed to Accept a socket with the specified timeout");
						} else if (selectResult == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "accept", "Failed to call select to wait for accept timeout!");
						}
						if (!FD_ISSET(socket, &acceptSet)) {
							throw NativeException(className, "accept", SYSTEM_EXCEPTION, "Select method returned normally without the server socket being set in the accepted fd set!");
						}
					}

					SOCKET clientSocket = INVALID_SOCKET;

					if (socketAddress.getHost().getFamily() == IPV4_FAMILY) {
						struct sockaddr_in sa;
						ZeroMemory( &sa, sizeof(sa));
						int nameLength = sizeof(sa);

						clientSocket = ::accept(socket, (struct sockaddr *) &sa, &nameLength);
						if (clientSocket == INVALID_SOCKET) {
							throw NativeException(className, "bind", SOCKET_EXCEPTION, "Server Socket is not bound yet");
						}

						memcpy(address, &sa.sin_addr, 4);
						if (getnameinfo((struct sockaddr *) &sa, sizeof(struct sockaddr_in), hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD) != 0) {
							WindowsUtils::handleLastWinSockError(className, "accept", "Failed to call getnameinfo to get host name from IPv4 address!");
						}
						inet_ntop(AF_INET, &sa.sin_addr, ipstringbuffer, INET6_ADDRSTRLEN);

						return new WindowsSocket(netFactory, clientSocket, NativeInetSocketAddress(NativeInetAddress(NativeString(hostname), NativeString(ipstringbuffer), IPV4_FAMILY, (jbyte *) address), ntohs(sa.sin_port)), socketAddress);

					} else {
						struct sockaddr_in6 sa;
						ZeroMemory( &sa, sizeof(sa));
						int nameLength = sizeof(sa);

						clientSocket = ::accept(socket, (struct sockaddr *) &sa, &nameLength);
						if (clientSocket == INVALID_SOCKET) {
							throw NativeException(className, "bind", SOCKET_EXCEPTION, "Server Socket is not bound yet");
						}

						memcpy(address, &sa.sin6_addr, 16);
						if (getnameinfo((struct sockaddr *) &sa, sizeof(struct sockaddr_in6), hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD) != 0) {
							WindowsUtils::handleLastWinSockError(className, "accept", "Failed to call getnameinfo to get host name from IPv6 address!");
						}
						if (WSAAddressToString((LPSOCKADDR) &sa, sizeof(struct sockaddr_in6), NULL, ipstringbuffer, &length) != 0) {
							WindowsUtils::handleLastWinSockError(className, "accept", "Failed to call WSAAddressToString for IPv6 address!");
						}

						return new WindowsSocket(netFactory, clientSocket, NativeInetSocketAddress(NativeInetAddress(NativeString(hostname), NativeString(ipstringbuffer), IPV6_FAMILY, (jbyte *) address), ntohs(sa.sin6_port)), socketAddress);

					}
				}

				void WindowsServerSocket::close() {
					ScopedLock synchronize(mutex);
					if (closed) {
						return;
					}
					if (closesocket(socket) == SOCKET_ERROR) {
						WindowsUtils::handleLastWinSockError(className, "close", "Failed to close the socket!");
					}
					closed = true;
				}

				jbool WindowsServerSocket::isBound() {
					ScopedLock synchronize(mutex);
					return bound;
				}

				jbool WindowsServerSocket::isClosed() {
					ScopedLock synchronize(mutex);
					return closed;
				}

				jint WindowsServerSocket::getReceiveBufferSize() {
					if(socket == INVALID_SOCKET) {
						return reuseAddress;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getReceiveBufferSize", SOCKET_EXCEPTION, "Server Socket is closed");
						}
						int optValue = 0;
						int optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_RCVBUF, (char *) &optValue, &optlen) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "getReceiveBufferSize", "Failed to call get socket option!");
						}
						return optValue;
					}
				}

				void WindowsServerSocket::setReceiveBufferSize(jint size) {
					if(socket == INVALID_SOCKET) {
						receiveBufferSizeSet = true;
						receiveBufferSize = size;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setReceiveBufferSize", SOCKET_EXCEPTION, "Server Socket is closed");
						}
						int optValue = size;
						if (setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (const char *) &optValue, sizeof(int)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "setReceiveBufferSize", "Failed to call set socket option!");
						}
					}
				}

				jbool WindowsServerSocket::getReuseAddress() {
					if(socket == INVALID_SOCKET) {
						return reuseAddress;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getReuseAddress", SOCKET_EXCEPTION, "Server Socket is closed");
						}
						int optValue = 0;
						int optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *) &optValue, &optlen) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "getReuseAddress", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void WindowsServerSocket::setReuseAddress(jbool on) {
					if(socket == INVALID_SOCKET) {
						reuseAddressSet = true;
						reuseAddress = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setReuseAddress", SOCKET_EXCEPTION, "Server Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &optValue, sizeof(int)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "setReuseAddress", "Failed to call set socket option!");
						}
					}
				}

				jint WindowsServerSocket::getSoTimeout() {
					if (isClosed()) {
						throw NativeException(className, "getSoTimeout", SOCKET_EXCEPTION, "Server Socket is closed");
					}
					return timeout;
				}

				void WindowsServerSocket::setSoTimeout(jint timeoutValue) {
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
