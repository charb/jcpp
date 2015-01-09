#include "jcpp/native/windows/net/WindowsSocket.h"
#include "jcpp/native/windows/net/WindowsNetFactory.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/api/nthread/ScopedLock.h"
#include "jcpp/native/windows/WindowsUtils.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::net;
using namespace jcpp::native::api::nthread;
using namespace std;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace net {

				NativeString WindowsSocket::className("jcpp::native::windows::net::WindowsSocket");

				WindowsSocket::WindowsSocket(WindowsNetFactory* nf) :
						NativeSocket(), netFactory(nf), mutex(), bound(false), closed(false), connected(false), socket(INVALID_SOCKET), inputStream(null), outputStream(null) {
				}

				WindowsSocket::WindowsSocket(WindowsNetFactory* nf,SOCKET socket, const NativeInetSocketAddress& remoteSocketAddress, const NativeInetSocketAddress& localSocketAddress) :
						NativeSocket(remoteSocketAddress, localSocketAddress), netFactory(nf), mutex(), bound(true), closed(false), connected(true), socket(socket) {
					inputStream = new WindowsSocketInputStream(socket);
					outputStream = new WindowsSocketOutputStream(socket);
				}

				WindowsSocket::~WindowsSocket() {
					try {
						close();
					} catch (...) {
						// TODO
					}

					delete inputStream;
					inputStream = null;

					delete outputStream;
					outputStream = null;
				}

				/**
				 * TODO Current implementation needs the local socket address to be configured with a correct ip address (get localhost from net factory)
				 * Update implementation to us ANY_ADDR host name (user created InetAddress)
				 */
				void WindowsSocket::bind(const NativeInetSocketAddress& _localSocketAddress) {
					ScopedLock synchronize(mutex);

					if (isClosed()) {
						throw NativeException(className, "bind", SOCKET_EXCEPTION, "Socket is closed!");
					}
					if (isBound()) {
						throw NativeException(className, "bind", SOCKET_EXCEPTION, "Socket is already bound!");
					}
					localSocketAddress = _localSocketAddress;

					if (socket == INVALID_SOCKET) {
						socket = ::socket(localSocketAddress.getHost().getFamily() == IPV4_FAMILY ? AF_INET : AF_INET6, SOCK_STREAM, IPPROTO_TCP);
						if (socket == INVALID_SOCKET) {
							WindowsUtils::handleLastWinSockError(className, "WindowsSocket", "Failed to Create a socket!");
						}

						if(keepAliveSet) {
							setKeepAlive(keepAlive);
						}
						if(oobInlineSet) {
							setOOBInline(oobInline);
						}
						if(receiveBufferSizeSet) {
							setReceiveBufferSize(receiveBufferSize);
						}
						if(reuseAddressSet) {
							setReuseAddress(reuseAddress);
						}
						if(sendBufferSizeSet) {
							setSendBufferSize(sendBufferSize);
						}
						if(tcpNoDelaySet) {
							setTcpNoDelay(tcpNoDelay);
						}

						inputStream = new WindowsSocketInputStream(socket);
						outputStream = new WindowsSocketOutputStream(socket);

						if(soTimeoutSet) {
							inputStream->setSoTimeout(soTimeout);
						}
					}

					NativeInetAddress localAddress = localSocketAddress.getHost();

					if (localAddress.getFamily() == IPV4_FAMILY) {
						jbyte addressBuf[4];
						localAddress.getAddress(addressBuf);

						struct sockaddr_in sa;
						ZeroMemory( &sa, sizeof(sa));

						sa.sin_family = AF_INET;
						sa.sin_port = htons(localSocketAddress.getPort());
						memcpy(&sa.sin_addr, addressBuf, 4);

						if (::bind(socket, (struct sockaddr *) &sa, sizeof(sa)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "bind", "Failed to Bind the Socket to the local socket inet address!");
						}

						int nameLength = sizeof(sa);
						if (getsockname(socket, (struct sockaddr *) &sa, &nameLength) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "bind", "Failed to get socket name information after binding to the local socket inet address!");
						}
						localSocketAddress = NativeInetSocketAddress(localSocketAddress.getHost(), ntohs(sa.sin_port));
					} else {
						jbyte addressBuf[16];
						localAddress.getAddress(addressBuf);

						struct sockaddr_in6 sa;
						ZeroMemory( &sa, sizeof(sa));

						sa.sin6_family = AF_INET6;
						sa.sin6_port = htons(localSocketAddress.getPort());
						memcpy(&sa.sin6_addr, addressBuf, 16);

						if (::bind(socket, (struct sockaddr *) &sa, sizeof(sa)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "bind", "Failed to Bind the Server Socket to the socket inet address!");
						}

						int nameLength = sizeof(sa);
						if (getsockname(socket, (struct sockaddr *) &sa, &nameLength) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "bind", "Failed to get socket name information after binding to the socket inet address!");
						}
						localSocketAddress = NativeInetSocketAddress(localSocketAddress.getHost(), ntohs(sa.sin6_port));
					}
					bound = true;
				}

				void WindowsSocket::connect(const NativeInetSocketAddress& _remoteSocketAddress, jint timeout) {
					if (timeout < 0) {
						throw NativeException(className, "connect", ILLEGAL_ARGUMENT_EXCEPTION, "connect: timeout can't be negative");
					}

					if (isClosed()) {
						throw NativeException(className, "connect", SOCKET_EXCEPTION, "Socket is closed");
					}

					if (isConnected()) {
						throw NativeException(className, "connect", SOCKET_EXCEPTION, "Socket is already connected");
					}

					if (!isBound()){
						bind(NativeInetSocketAddress(netFactory->getLocalHost(),0));
					}

					remoteSocketAddress = _remoteSocketAddress;

					NativeInetAddress remoteAddress = remoteSocketAddress.getHost();

					struct sockaddr_in sa;
					struct sockaddr_in6 sa6;

					struct sockaddr * psa = null;
					int saLength = 0;

					if (remoteAddress.getFamily() == IPV4_FAMILY) {
						ZeroMemory( &sa, sizeof(sa));
						jbyte addressBuf[4];
						remoteAddress.getAddress(addressBuf);

						sa.sin_family = AF_INET;
						sa.sin_port = htons(remoteSocketAddress.getPort());
						memcpy(&sa.sin_addr, addressBuf, 4);

						psa = (struct sockaddr *) &sa;
						saLength = sizeof(sa);
					} else {
						ZeroMemory( &sa6, sizeof(sa6));
						jbyte addressBuf[16];
						remoteAddress.getAddress(addressBuf);

						sa6.sin6_family = AF_INET6;
						sa6.sin6_port = htons(remoteSocketAddress.getPort());
						memcpy(&sa6.sin6_addr, addressBuf, 16);

						psa = (struct sockaddr *) &sa6;
						saLength = sizeof(sa6);
					}

					/* The result of the connection */
					if (timeout <= 0) {
						int connectResult = ::connect(socket, psa, saLength);
						if ((connectResult == SOCKET_ERROR) || (connectResult != 0)) {
							WindowsUtils::handleLastWinSockError(className, "connect", "Failed to connect to the remote socket inet Address!");
						}
					} else {
						int connect_res;
						u_long optval;
						int optlen = sizeof(optval);

						/* make socket non-blocking */
						optval = 1;
						ioctlsocket(socket, FIONBIO, &optval);

						/* initiate the connect */
						connect_res = ::connect(socket, psa, saLength);
						if (connect_res == SOCKET_ERROR) {
							if (WSAGetLastError() != WSAEWOULDBLOCK) {
								connect_res = WSAGetLastError();
							} else {
								fd_set wr, ex;
								struct timeval t;

								FD_ZERO(&wr);
								FD_ZERO(&ex);
								FD_SET(socket, &wr);
								FD_SET(socket, &ex);
								t.tv_sec = timeout / 1000;
								t.tv_usec = (timeout % 1000) * 1000;

								/*
								 * Wait for timout, connection established or
								 * connection failed.
								 */
								connect_res = select(0, 0, &wr, &ex, &t);

								/*
								 * Timeout before connection is established/failed so
								 * we throw exception and shutdown input/output to prevent
								 * socket from being used.
								 * The socket should be closed immediately by the caller.
								 */
								if (connect_res == 0) {
									shutdown(socket, SD_BOTH);

									/* make socket blocking again*/
									optval = 0;
									ioctlsocket(socket, FIONBIO, &optval);

									throw NativeException(className, "connect", SOCKET_TIMEOUT_EXCEPTION, "Failed to connect to remote socket with the specified timeout");
								}

								/*
								 * We must now determine if the connection has been established
								 * or if it has failed. The logic here is designed to work around
								 * bug on Windows NT whereby using getsockopt to obtain the
								 * last error (SO_ERROR) indicates there is no error. The workaround
								 * on NT is to allow winsock to be scheduled and this is done by
								 * yielding and retrying. As yielding is problematic in heavy
								 * load conditions we attempt up to 3 times to get the error reason.
								 */
								if (!FD_ISSET(socket, &ex)) {
									connect_res = 0;
								} else {
									int retry;
									optlen = sizeof(connect_res);
									for (retry = 0; retry < 3; retry++) {
										getsockopt(socket, SOL_SOCKET, SO_ERROR, (char*) &connect_res, &optlen);
										if (connect_res) {
											break;
										}
										Sleep(0);
									}

									if (connect_res == 0) {
										optval = 0;
										ioctlsocket(socket, FIONBIO, &optval);
										throw NativeException(className, "connect", SOCKET_EXCEPTION, "Unable to establish connection");
										return;
									}
								}
							}
						}

						/* make socket blocking again */
						optval = 0;
						ioctlsocket(socket, FIONBIO, &optval);

						if (connect_res) {
							if (connect_res == WSAEADDRNOTAVAIL) {
								throw NativeException(className, "connect", CONNECT_EXCEPTION, "connect: Address is invalid on local machine, or port is not valid on remote machine");
							} else {
								WindowsUtils::handleLastWinSockError(connect_res, className, "connect", "Failed to connect to the remote socket inet Address!");
							}
							return;
						}
					}

					connected = true;
				}

				void WindowsSocket::close() {
					ScopedLock synchronize(mutex);
					if (closed || (socket == INVALID_SOCKET)) {
						return;
					}
					if (closesocket(socket) == SOCKET_ERROR) {
						WindowsUtils::handleLastWinSockError(className, "close", "Failed to close the socket!");
					}
					inputStream->markSocketClosed();
					outputStream->markSocketClosed();
					closed = true;
				}

				NativeInputStream * WindowsSocket::getInputStream() {
					if (isClosed()) {
						throw NativeException(className, "getInputStream", SOCKET_EXCEPTION, "Socket is closed");
					}
					if (!isConnected()) {
						throw NativeException(className, "getInputStream", SOCKET_EXCEPTION, "Socket is still not connected");
					}
					return inputStream;
				}

				NativeOutputStream * WindowsSocket::getOutputStream() {
					if (isClosed()) {
						throw NativeException(className, "getOutputStream", SOCKET_EXCEPTION, "Socket is closed");
					}
					if (!isConnected()) {
						throw NativeException(className, "getOutputStream", SOCKET_EXCEPTION, "Socket is still not connected");
					}
					return outputStream;
				}

				void WindowsSocket::shutdownInput() {
					if (isClosed()) {
						throw NativeException(className, "shutdownInput", SOCKET_EXCEPTION, "Socket is closed");
					}
					if(inputStream != null) {
						inputStream->close();
					}
				}

				void WindowsSocket::shutdownOutput() {
					if (isClosed()) {
						throw NativeException(className, "shutdownOutput", SOCKET_EXCEPTION, "Socket is closed");
					}
					if(outputStream != null) {
						outputStream->close();
					}
				}

				jbool WindowsSocket::isInputShutdown() {
					if (isClosed()) {
						throw NativeException(className, "isInputShutdown", SOCKET_EXCEPTION, "Socket is closed");
					}
					return (inputStream != null) && (inputStream->isStreamClosed());
				}

				jbool WindowsSocket::isOutputShutdown() {
					if (isClosed()) {
						throw NativeException(className, "isOutputShutdown", SOCKET_EXCEPTION, "Socket is closed");
					}
					return (outputStream != null) && (outputStream->isStreamClosed());
				}

				jbool WindowsSocket::isBound() {
					ScopedLock synchronize(mutex);
					return bound;
				}

				jbool WindowsSocket::isClosed() {
					ScopedLock synchronize(mutex);
					return closed;
				}

				jbool WindowsSocket::isConnected() {
					ScopedLock synchronize(mutex);
					return connected;
				}

				void WindowsSocket::sendUrgentData(jbyte data) {
					if (isClosed()) {
						throw NativeException(className, "sendUrgentData", SOCKET_EXCEPTION, "Socket is closed");
					}
					if (!isConnected()) {
						throw NativeException(className, "sendUrgentData", SOCKET_EXCEPTION, "Socket is still not connected");
					}
					if (send(socket, (char *) &data, 1, MSG_OOB) == SOCKET_ERROR) {
						WindowsUtils::handleLastWinSockError(className, "sendUrgentData", "Failed to send urgent data!");
					}
				}

				jbool WindowsSocket::getKeepAlive() {
					if(socket == INVALID_SOCKET) {
						return keepAlive;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getKeepAlive", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						int optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (char *) &optValue, &optlen) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "getKeepAlive", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void WindowsSocket::setKeepAlive(jbool on) {
					if(socket == INVALID_SOCKET) {
						keepAliveSet = true;
						keepAlive = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setKeepAlive", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (const char *) &optValue, sizeof(int)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "setKeepAlive", "Failed to call set socket option!");
						}
					}
				}

				jbool WindowsSocket::getOOBInline() {
					if(socket == INVALID_SOCKET) {
						return oobInline;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getOOBInline", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						int optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_OOBINLINE, (char *) &optValue, &optlen) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "getOOBInline", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void WindowsSocket::setOOBInline(jbool on) {
					if(socket == INVALID_SOCKET) {
						oobInlineSet = true;
						oobInline = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setOOBInline", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, SO_OOBINLINE, (const char *) &optValue, sizeof(int)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "setOOBInline", "Failed to call set socket option!");
						}
					}
				}

				jint WindowsSocket::getReceiveBufferSize() {
					if(socket == INVALID_SOCKET) {
						return receiveBufferSize;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getReceiveBufferSize", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						int optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_RCVBUF, (char *) &optValue, &optlen) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "getReceiveBufferSize", "Failed to call get socket option!");
						}
						return optValue;
					}
				}

				void WindowsSocket::setReceiveBufferSize(jint size) {
					if(socket == INVALID_SOCKET) {
						receiveBufferSizeSet = true;
						receiveBufferSize = size;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setReceiveBufferSize", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = size;
						if (setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (const char *) &optValue, sizeof(int)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "setReceiveBufferSize", "Failed to call set socket option!");
						}
					}
				}

				jbool WindowsSocket::getReuseAddress() {
					if(socket == INVALID_SOCKET) {
						return reuseAddress;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getReuseAddress", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						int optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *) &optValue, &optlen) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "getReuseAddress", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void WindowsSocket::setReuseAddress(jbool on) {
					if(socket == INVALID_SOCKET) {
						reuseAddressSet = true;
						reuseAddress = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setReuseAddress", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &optValue, sizeof(int)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "setReuseAddress", "Failed to call set socket option!");
						}
					}
				}

				jint WindowsSocket::getSendBufferSize() {
					if(socket == INVALID_SOCKET) {
						return sendBufferSize;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getSendBufferSize", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						int optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_SNDBUF, (char *) &optValue, &optlen) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "getSendBufferSize", "Failed to call get socket option!");
						}
						return optValue;
					}
				}

				void WindowsSocket::setSendBufferSize(jint size) {
					if(socket == INVALID_SOCKET) {
						sendBufferSizeSet = true;
						sendBufferSize = size;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setSendBufferSize", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = size;
						if (setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (const char *) &optValue, sizeof(int)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "setSendBufferSize", "Failed to call set socket option!");
						}
					}
				}

				jint WindowsSocket::getSoLinger() {
					if(socket == INVALID_SOCKET) {
						return soLinger;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getSoLinger", SOCKET_EXCEPTION, "Socket is closed");
						}
						LINGER ln;
						int optlen = sizeof(ln);
						if (getsockopt(socket, SOL_SOCKET, SO_LINGER, (char *) &ln, &optlen) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "getSoLinger", "Failed to call get socket option!");
						}
						return ln.l_onoff == 0 ? -1 : ln.l_linger;
					}
				}

				void WindowsSocket::setSoLinger(jbool on, jint linger) {
					if(socket == INVALID_SOCKET) {
						soLingerSet = true;
						soLingerOn = on;
						soLinger = linger;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setSoLinger", SOCKET_EXCEPTION, "Socket is closed");
						}
						LINGER ln;
						ln.l_onoff = on ? 1 : 0;
						ln.l_linger = linger;
						if (setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (const char *) &ln, sizeof(ln)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "setSoLinger", "Failed to call set socket option!");
						}
					}
				}

				jint WindowsSocket::getSoTimeout() {
					if(socket == INVALID_SOCKET) {
						return soTimeout;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getSoTimeout", SOCKET_EXCEPTION, "Socket is closed");
						}
						return inputStream->getSoTimeout();
					}
				}

				void WindowsSocket::setSoTimeout(jint timeout) {
					if(socket == INVALID_SOCKET) {
						soTimeoutSet = true;
						soTimeout = timeout;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setSoTimeout", SOCKET_EXCEPTION, "Socket is closed");
						}
						if (timeout < 0) {
							throw NativeException(className, "setSoTimeout", ILLEGAL_ARGUMENT_EXCEPTION, "Invalid negative socket timeout value!");
						}
						inputStream->setSoTimeout(timeout);
					}
				}

				jbool WindowsSocket::getTcpNoDelay() {
					if(socket == INVALID_SOCKET) {
						return tcpNoDelay;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getTcpNoDelay", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						int optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, TCP_NODELAY, (char *) &optValue, &optlen) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "getTcpNoDelay", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void WindowsSocket::setTcpNoDelay(jbool on) {
					if(socket == INVALID_SOCKET) {
						tcpNoDelaySet = true;
						tcpNoDelay = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setTcpNoDelay", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, TCP_NODELAY, (const char *) &optValue, sizeof(int)) == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "setTcpNoDelay", "Failed to call set socket option!");
						}
					}
				}

			}
		}
	}
}
