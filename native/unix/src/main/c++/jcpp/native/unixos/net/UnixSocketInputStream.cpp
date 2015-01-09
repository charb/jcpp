#include "jcpp/native/unixos/net/UnixSocketInputStream.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/unixos/UnixUtils.h"

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#if defined(SOLARIS2)
#include <sys/filio.h>
#elif defined(Linux) || defined(_AIX)
#include <sys/ioctl.h>
#endif

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				NativeString UnixSocketInputStream::className("jcpp::native::unixos::net::UnixSocketInputStream");

				UnixSocketInputStream::UnixSocketInputStream(int socket) :
						socket(socket), eof(false), timeout(0), streamClosed(false), socketClosed(false) {
				}

				UnixSocketInputStream::~UnixSocketInputStream() {
				}

				jbyte UnixSocketInputStream::read() {
					if (eof) {
						return -1;
					}
					jbyte byte = 0;
					int n = read(&byte, 0, 1);
					if (n < 0) {
						return -1;
					}
					return byte;
				}

				jint UnixSocketInputStream::read(jbyte * buf, jint offset, jint length) {
					if (streamClosed) {
						throw NativeException(className, "read", IO_EXCEPTION, "Socket Input Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "read", IO_EXCEPTION, "Socket is closed");
					}

					if (eof) {
						return -1;
					}

					if (timeout > 0) {
						jlong selectTimeout = timeout;
						while (true) {
							fd_set readSet;
							FD_ZERO(&readSet);
							FD_SET(socket, &readSet);

							struct timeval tv;
							UnixUtils::longToTimeval(tv, timeout);

							jlong startTime = UnixUtils::getCurrentTimeMillis();
							int selectResult = select(FD_SETSIZE, &readSet, NULL, NULL, &tv);
							jlong endTime = UnixUtils::getCurrentTimeMillis();

							if (selectResult == 0) {
								throw NativeException(className, "read", SOCKET_TIMEOUT_EXCEPTION, "Failed to read from a socket with the specified timeout");
							} else if (selectResult == -1) {
								if (errno == EINTR) {
									selectTimeout -= (endTime - startTime);
									if (selectTimeout <= 0) {
										throw NativeException(className, "read", SOCKET_TIMEOUT_EXCEPTION, "Failed to read from a socket with the specified timeout");
									}
									continue;
								}
								UnixUtils::handleLastSocketError(className, "read", "Failed to call select to wait for read timeout!");
							}
							if (!FD_ISSET(socket, &readSet)) {
								throw NativeException(className, "read", SYSTEM_EXCEPTION, "Select method returned normally without the socket being set in the read fd set!");
							}
							break;
						}
					}

					EINTR_RETRY(recv(socket, (char * ) (buf + offset), length, 0))

					if (result == -1) {
						UnixUtils::handleLastSocketError(className, "read", "Failed to read from the socket input stream!");
						return -1;
					} else if (result == 0) {
						eof = true;
						return -1;
					} else {
						return result;
					}
				}

				jlong UnixSocketInputStream::skip(jlong offset) {
					if (streamClosed) {
						throw NativeException(className, "skip", IO_EXCEPTION, "Socket Input Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "skip", IO_EXCEPTION, "Socket is closed");
					}
					if (offset < 0) {
						return 0;
					}
					jlong n = offset;
					jbyte data[1024];
					while (n > 0) {
						int r = read(data, 0, 1024 < n ? 1024 : n);
						if (r < 0) {
							break;
						}
						n -= r;
					}
					return offset - n;
				}

				jlong UnixSocketInputStream::available() {
					if (streamClosed) {
						throw NativeException(className, "available", IO_EXCEPTION, "Socket Input Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "available", IO_EXCEPTION, "Socket is closed");
					}
					u_long availableBytes = 0;
					EINTR_RETRY(ioctl(socket, FIONREAD, &availableBytes))
					if (result == -1) {
						UnixUtils::handleLastSocketError(className, "available", "Failed to get the available bytes to read from the socket!");
					}
					return (jlong) availableBytes;
				}

				void UnixSocketInputStream::close() {
					if (streamClosed || socketClosed) {
						return;
					}
					if (shutdown(socket, SHUT_RD) == -1) {
						UnixUtils::handleLastSocketError(className, "close", "Failed to close the input stream of the socket!");
					}
					streamClosed = true;
				}

				void UnixSocketInputStream::markSocketClosed() {
					socketClosed = true;
				}

				jbool UnixSocketInputStream::isStreamClosed() {
					return streamClosed;
				}

				jint UnixSocketInputStream::getSoTimeout() {
					return timeout;
				}

				void UnixSocketInputStream::setSoTimeout(jint timeoutValue) {
					timeout = timeoutValue;
				}

			}
		}
	}
}
