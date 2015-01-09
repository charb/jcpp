#include "jcpp/native/unixos/net/UnixSocket.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/api/nthread/ScopedLock.h"
#include "jcpp/native/unixos/UnixUtils.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::net;
using namespace jcpp::native::api::nthread;

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/tcp.h>

#define SET_NONBLOCKING(fd) {           \
        int flags1 = fcntl(fd, F_GETFL); \
        flags1 |= O_NONBLOCK;            \
        fcntl(fd, F_SETFL, flags1);      \
}

#define SET_BLOCKING(fd) {              \
        int flags2 = fcntl(fd, F_GETFL); \
        flags2 &= ~O_NONBLOCK;           \
        fcntl(fd, F_SETFL, flags2);      \
}

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				NativeString UnixSocket::className("jcpp::native::unixos::net::UnixSocket");

				UnixSocket::UnixSocket() :
						NativeSocket(), mutex(), bound(false), closed(false), connected(false), socket(-1), inputStream(null), outputStream(null) {
				}

				UnixSocket::UnixSocket(int socket, const NativeInetSocketAddress& remoteSocketAddress, const NativeInetSocketAddress& localSocketAddress) :
						NativeSocket(remoteSocketAddress, localSocketAddress), mutex(), bound(true), closed(false), connected(true), socket(socket) {
					inputStream = new UnixSocketInputStream(socket);
					outputStream = new UnixSocketOutputStream(socket);
				}

				UnixSocket::~UnixSocket() {
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
				void UnixSocket::bind(const NativeInetSocketAddress& _localSocketAddress) {
					ScopedLock synchronize(mutex);

					if (isClosed()) {
						throw NativeException(className, "bind", SOCKET_EXCEPTION, "Socket is closed!");
					}
					if (isBound()) {
						throw NativeException(className, "bind", SOCKET_EXCEPTION, "Socket is already bound!");
					}
					localSocketAddress = _localSocketAddress;

					if (socket == -1) {
						socket = ::socket(localSocketAddress.getHost().getFamily() == IPV4_FAMILY ? AF_INET : AF_INET6, SOCK_STREAM, IPPROTO_TCP);
						if (socket == -1) {
							UnixUtils::handleLastSocketError(className, "UnixSocket", "Failed to Create a socket!");
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

						inputStream = new UnixSocketInputStream(socket);
						outputStream = new UnixSocketOutputStream(socket);

						if(soTimeoutSet) {
							inputStream->setSoTimeout(soTimeout);
						}
					}

					NativeInetAddress localAddress = localSocketAddress.getHost();

					if (localAddress.getFamily() == IPV4_FAMILY) {
						jbyte addressBuf[4];
						localAddress.getAddress(addressBuf);

						struct sockaddr_in sa;
						memset(&sa, 0, sizeof(sa));

						sa.sin_family = AF_INET;
						sa.sin_port = htons(localSocketAddress.getPort());
						memcpy(&sa.sin_addr, addressBuf, 4);

						if (::bind(socket, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
							UnixUtils::handleLastSocketError(className, "bind", "Failed to Bind the Socket to the local socket inet address!");
						}

						socklen_t nameLength = (socklen_t) sizeof(sa);
						if (getsockname(socket, (struct sockaddr *) &sa, &nameLength) == -1) {
							UnixUtils::handleLastSocketError(className, "bind", "Failed to get socket name information after binding to the local socket inet address!");
						}
						localSocketAddress = NativeInetSocketAddress(localSocketAddress.getHost(), ntohs(sa.sin_port));
					} else {
						jbyte addressBuf[16];
						localAddress.getAddress(addressBuf);

						struct sockaddr_in6 sa;
						memset(&sa, 0, sizeof(sa));

						sa.sin6_family = AF_INET6;
						sa.sin6_port = htons(localSocketAddress.getPort());
						memcpy(&sa.sin6_addr, addressBuf, 16);

						if (::bind(socket, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
							UnixUtils::handleLastSocketError(className, "bind", "Failed to Bind the Server Socket to the socket inet address!");
						}

						socklen_t nameLength = (socklen_t) sizeof(sa);
						if (getsockname(socket, (struct sockaddr *) &sa, &nameLength) == -1) {
							UnixUtils::handleLastSocketError(className, "bind", "Failed to get socket name information after binding to the socket inet address!");
						}
						localSocketAddress = NativeInetSocketAddress(localSocketAddress.getHost(), ntohs(sa.sin6_port));
					}
					bound = true;
				}

				void UnixSocket::connect(const NativeInetSocketAddress& _remoteSocketAddress, jint timeout) {
					if (timeout < 0) {
						throw NativeException(className, "connect", ILLEGAL_ARGUMENT_EXCEPTION, "connect: timeout can't be negative");
					}

					if (isClosed()) {
						throw NativeException(className, "connect", SOCKET_EXCEPTION, "Socket is closed");
					}

					if (isConnected()) {
						throw NativeException(className, "connect", SOCKET_EXCEPTION, "Socket is already connected");
					}

					remoteSocketAddress = _remoteSocketAddress;

					NativeInetAddress remoteAddress = remoteSocketAddress.getHost();

					struct sockaddr_in sa;
					struct sockaddr_in6 sa6;

					struct sockaddr * psa = null;
					int saLength = 0;

					if (remoteAddress.getFamily() == IPV4_FAMILY) {
						memset(&sa, 0, sizeof(sa));
						jbyte addressBuf[4];
						remoteAddress.getAddress(addressBuf);

						sa.sin_family = AF_INET;
						sa.sin_port = htons(remoteSocketAddress.getPort());
						memcpy(&sa.sin_addr, addressBuf, 4);

						psa = (struct sockaddr *) &sa;
						saLength = sizeof(sa);
					} else {
						memset(&sa6, 0, sizeof(sa6));
						jbyte addressBuf[16];
						remoteAddress.getAddress(addressBuf);

						sa6.sin6_family = AF_INET6;
						sa6.sin6_port = htons(remoteSocketAddress.getPort());
						memcpy(&sa6.sin6_addr, addressBuf, 16);

						psa = (struct sockaddr *) &sa6;
						saLength = sizeof(sa6);
					}

					int connectResult = 0;

					if (timeout <= 0) {
						EINTR_RETRY_R(connectResult, ::connect(socket, psa, saLength))
						if (connectResult != 0) {

							UnixUtils::handleLastSocketError(className, "connect", "Failed to connect to the remote socket inet Address!");
						}
					} else {
						/* make socket non-blocking */
						SET_NONBLOCKING(socket);

						/* initiate the connect */
						connectResult = ::connect(socket, psa, saLength);
						if (connectResult != 0) {
							int errnoValue = errno;
							if (errnoValue != EINPROGRESS && errnoValue != EACCES) {
								SET_BLOCKING(socket);
								UnixUtils::handleLastSocketError(className, "connect", "Failed to connect to the remote socket inet Address!");
							}
							jlong selectTimeout = timeout;
							while (true) {
								fd_set wr, ex;

								struct timeval t;
								UnixUtils::longToTimeval(t, (jlong) selectTimeout);

								FD_ZERO(&wr);
								FD_ZERO(&ex);
								FD_SET(socket, &wr);
								FD_SET(socket, &ex);

								jlong startTime = UnixUtils::getCurrentTimeMillis();
								int selectResult = select(FD_SETSIZE, 0, &wr, &ex, &t);
								jlong endTime = UnixUtils::getCurrentTimeMillis();

								if (selectResult == -1 && errno == EINTR) {
									selectTimeout -= (endTime - startTime);
									if (selectTimeout <= 0) {
										SET_BLOCKING(socket);
										shutdown(socket, SHUT_RDWR);
										throw NativeException(className, "connect", SOCKET_TIMEOUT_EXCEPTION, "Failed to connect to remote socket with the specified timeout");
									}
									continue;
								}

								SET_BLOCKING(socket);

								/*
								 * Timeout before connection is established/failed so
								 * we throw exception and shutdown input/output to prevent
								 * socket from being used.
								 * The socket should be closed immediately by the caller.
								 */
								if (selectResult == 0) {
									shutdown(socket, SHUT_RDWR);
									throw NativeException(className, "connect", SOCKET_TIMEOUT_EXCEPTION, "Failed to connect to remote socket with the specified timeout");
								} else if (selectResult == -1) {
									UnixUtils::handleLastSocketError(className, "connect", "Failed to call select to wait for connect timeout!");
								}

								if (FD_ISSET(socket, &ex)) {
									// Error occurred while connecting
									int optValue = 0;
									socklen_t optlen = sizeof(optValue);
									if (getsockopt(socket, SOL_SOCKET, SO_ERROR, (char*) &optValue, &optlen) == -1) {
										throw NativeException(className, "connect", SOCKET_EXCEPTION, "Unable to establish connection");
									} else {
										UnixUtils::handleLastSocketError(optValue, className, "connect", "Failed to connect");
									}
								}

								// connected successfully
								break;
							}
						}
					}

					connected = true;
				}

				void UnixSocket::close() {
					ScopedLock synchronize(mutex);
					if (closed || (socket == -1)) {
						return;
					}
					EINTR_RETRY(::close(socket))
					if (result == -1) {
						UnixUtils::handleLastSocketError(className, "close", "Failed to close the socket!");
					}
					inputStream->markSocketClosed();
					outputStream->markSocketClosed();
					closed = true;
				}

				NativeInputStream * UnixSocket::getInputStream() {
					if (isClosed()) {
						throw NativeException(className, "getInputStream", SOCKET_EXCEPTION, "Socket is closed");
					}
					if (!isConnected()) {
						throw NativeException(className, "getInputStream", SOCKET_EXCEPTION, "Socket is still not connected");
					}
					return inputStream;
				}

				NativeOutputStream * UnixSocket::getOutputStream() {
					if (isClosed()) {
						throw NativeException(className, "getOutputStream", SOCKET_EXCEPTION, "Socket is closed");
					}
					if (!isConnected()) {
						throw NativeException(className, "getOutputStream", SOCKET_EXCEPTION, "Socket is still not connected");
					}
					return outputStream;
				}

				void UnixSocket::shutdownInput() {
					if (isClosed()) {
						throw NativeException(className, "shutdownInput", SOCKET_EXCEPTION, "Socket is closed");
					}
					if(inputStream != null) {
						inputStream->close();
					}
				}

				void UnixSocket::shutdownOutput() {
					if (isClosed()) {
						throw NativeException(className, "shutdownOutput", SOCKET_EXCEPTION, "Socket is closed");
					}
					if(outputStream != null) {
						outputStream->close();
					}
				}

				jbool UnixSocket::isInputShutdown() {
					if (isClosed()) {
						throw NativeException(className, "isInputShutdown", SOCKET_EXCEPTION, "Socket is closed");
					}
					return (inputStream != null) && (inputStream->isStreamClosed());
				}

				jbool UnixSocket::isOutputShutdown() {
					if (isClosed()) {
						throw NativeException(className, "isOutputShutdown", SOCKET_EXCEPTION, "Socket is closed");
					}
					return (outputStream != null) && (outputStream->isStreamClosed());
				}

				jbool UnixSocket::isBound() {
					ScopedLock synchronize(mutex);
					return bound;
				}

				jbool UnixSocket::isClosed() {
					ScopedLock synchronize(mutex);
					return closed;
				}

				jbool UnixSocket::isConnected() {
					ScopedLock synchronize(mutex);
					return connected;
				}

				void UnixSocket::sendUrgentData(jbyte data) {
					if (isClosed()) {
						throw NativeException(className, "sendUrgentData", SOCKET_EXCEPTION, "Socket is closed");
					}
					if (!isConnected()) {
						throw NativeException(className, "sendUrgentData", SOCKET_EXCEPTION, "Socket is still not connected");
					}
					if (send(socket, (char *) &data, 1, MSG_OOB) == -1) {
						UnixUtils::handleLastSocketError(className, "sendUrgentData", "Failed to send urgent data!");
					}
				}

				jbool UnixSocket::getKeepAlive() {
					if(socket == -1) {
						return keepAlive;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getKeepAlive", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						socklen_t optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (char *) &optValue, &optlen) == -1) {
							UnixUtils::handleLastSocketError(className, "getKeepAlive", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void UnixSocket::setKeepAlive(jbool on) {
					if(socket == -1) {
						keepAliveSet = true;
						keepAlive = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setKeepAlive", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (const char *) &optValue, sizeof(int)) == -1) {
							UnixUtils::handleLastSocketError(className, "setKeepAlive", "Failed to call set socket option!");
						}
					}
				}

				jbool UnixSocket::getOOBInline() {
					if(socket == -1) {
						return oobInline;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getOOBInline", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						socklen_t optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_OOBINLINE, (char *) &optValue, &optlen) == -1) {
							UnixUtils::handleLastSocketError(className, "getOOBInline", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void UnixSocket::setOOBInline(jbool on) {
					if(socket == -1) {
						oobInlineSet = true;
						oobInline = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setOOBInline", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, SO_OOBINLINE, (const char *) &optValue, sizeof(int)) == -1) {
							UnixUtils::handleLastSocketError(className, "setOOBInline", "Failed to call set socket option!");
						}
					}
				}

				jint UnixSocket::getReceiveBufferSize() {
					if(socket == -1) {
						return receiveBufferSize;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getReceiveBufferSize", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						socklen_t optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_RCVBUF, (char *) &optValue, &optlen) == -1) {
							UnixUtils::handleLastSocketError(className, "getReceiveBufferSize", "Failed to call get socket option!");
						}
						return optValue;
					}
				}

				void UnixSocket::setReceiveBufferSize(jint size) {
					if(socket == -1) {
						receiveBufferSizeSet = true;
						receiveBufferSize = size;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setReceiveBufferSize", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = size;
						if (setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (const char *) &optValue, sizeof(int)) == -1) {
							UnixUtils::handleLastSocketError(className, "setReceiveBufferSize", "Failed to call set socket option!");
						}
					}
				}

				jbool UnixSocket::getReuseAddress() {
					if(socket == -1) {
						return reuseAddress;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getReuseAddress", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						socklen_t optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *) &optValue, &optlen) == -1) {
							UnixUtils::handleLastSocketError(className, "getReuseAddress", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void UnixSocket::setReuseAddress(jbool on) {
					if(socket == -1) {
						reuseAddressSet = true;
						reuseAddress = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setReuseAddress", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &optValue, sizeof(int)) == -1) {
							UnixUtils::handleLastSocketError(className, "setReuseAddress", "Failed to call set socket option!");
						}
					}
				}

				jint UnixSocket::getSendBufferSize() {
					if(socket == -1) {
						return sendBufferSize;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getSendBufferSize", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						socklen_t optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, SO_SNDBUF, (char *) &optValue, &optlen) == -1) {
							UnixUtils::handleLastSocketError(className, "getSendBufferSize", "Failed to call get socket option!");
						}
						return optValue;
					}
				}

				void UnixSocket::setSendBufferSize(jint size) {
					if(socket == -1) {
						sendBufferSizeSet = true;
						sendBufferSize = size;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setSendBufferSize", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = size;
						if (setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (const char *) &optValue, sizeof(int)) == -1) {
							UnixUtils::handleLastSocketError(className, "setSendBufferSize", "Failed to call set socket option!");
						}
					}
				}

				jint UnixSocket::getSoLinger() {
					if(socket == -1) {
						return soLinger;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getSoLinger", SOCKET_EXCEPTION, "Socket is closed");
						}
						struct linger ln;
						socklen_t optlen = (socklen_t) sizeof(ln);
						if (getsockopt(socket, SOL_SOCKET, SO_LINGER, (char *) &ln, &optlen) == -1) {
							UnixUtils::handleLastSocketError(className, "getSoLinger", "Failed to call get socket option!");
						}
						return ln.l_onoff == 0 ? -1 : ln.l_linger;
					}
				}

				void UnixSocket::setSoLinger(jbool on, jint linger) {
					if(socket == -1) {
						soLingerSet = true;
						soLingerOn = on;
						soLinger = linger;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setSoLinger", SOCKET_EXCEPTION, "Socket is closed");
						}
						struct linger ln;
						ln.l_onoff = on ? 1 : 0;
						ln.l_linger = linger;
						if (setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (const char *) &ln, sizeof(ln)) == -1) {
							UnixUtils::handleLastSocketError(className, "setSoLinger", "Failed to call set socket option!");
						}
					}
				}

				jint UnixSocket::getSoTimeout() {
					if(socket == -1) {
						return soTimeout;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getSoTimeout", SOCKET_EXCEPTION, "Socket is closed");
						}
						return inputStream->getSoTimeout();
					}
				}

				void UnixSocket::setSoTimeout(jint timeout) {
					if(socket == -1) {
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

				jbool UnixSocket::getTcpNoDelay() {
					if(socket == -1) {
						return tcpNoDelay;
					} else {
						if (isClosed()) {
							throw NativeException(className, "getTcpNoDelay", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = 0;
						socklen_t optlen = 0;
						if (getsockopt(socket, SOL_SOCKET, TCP_NODELAY, (char *) &optValue, &optlen) == -1) {
							UnixUtils::handleLastSocketError(className, "getTcpNoDelay", "Failed to call get socket option!");
						}
						return optValue != 0;
					}
				}

				void UnixSocket::setTcpNoDelay(jbool on) {
					if(socket == -1) {
						tcpNoDelaySet = true;
						tcpNoDelay = on;
					} else {
						if (isClosed()) {
							throw NativeException(className, "setTcpNoDelay", SOCKET_EXCEPTION, "Socket is closed");
						}
						int optValue = on ? 1 : 0;
						if (setsockopt(socket, SOL_SOCKET, TCP_NODELAY, (const char *) &optValue, sizeof(int)) == -1) {
							UnixUtils::handleLastSocketError(className, "setTcpNoDelay", "Failed to call set socket option!");
						}
					}
				}

			}
		}
	}
}
