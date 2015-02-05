#include "jcpp/native/windows/net/WindowsSocketInputStream.h"
#include "jcpp/native/api/NativeException.h"
#include <iostream>

using namespace std;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace net {

				NativeString WindowsSocketInputStream::className("jcpp::native::windows::net::WindowsSocketInputStream");

				WindowsSocketInputStream::WindowsSocketInputStream(SOCKET socket) :
						socket(socket), streamClosed(false), socketClosed(false), eof(false), timeout(0) {
				}

				WindowsSocketInputStream::~WindowsSocketInputStream() {
				}

				jbyte WindowsSocketInputStream::read() {
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

				jint WindowsSocketInputStream::read(jbyte * buf, jint offset, jint length) {
					if (streamClosed) {
						throw NativeException(className, "read", SOCKET_EXCEPTION, "Socket Input Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "read", SOCKET_EXCEPTION, "Socket is closed");
					}

					if (eof) {
						return -1;
					}

					if (timeout > 0) {
						fd_set readSet;
						FD_ZERO(&readSet);
						FD_SET(socket, &readSet);

						struct timeval tv;
						WindowsUtils::longToTimeval(tv, timeout);

						int selectResult = select(0, &readSet, NULL, NULL, &tv);
						if (selectResult == 0) {
							throw NativeException(className, "read", SOCKET_TIMEOUT_EXCEPTION, "Failed to read from a socket with the specified timeout");
						} else if (selectResult == SOCKET_ERROR) {
							WindowsUtils::handleLastWinSockError(className, "accept", "Failed to call select to wait for read timeout!");
						}
						if (!FD_ISSET(socket, &readSet)) {
							throw NativeException(className, "read", SYSTEM_EXCEPTION, "Select method returned normally without the socket being set in the read fd set!");
						}
					}

					int result = recv(socket, (char *) (buf + offset), length, 0);

					if (result == SOCKET_ERROR) {
						WindowsUtils::handleLastWinSockError(className, "read", "Failed to read from the socket input stream!");
						return -1;
					} else if (result == 0) {
						eof = true;
						return -1;
					} else {
						return result;
					}
				}

				jlong WindowsSocketInputStream::skip(jlong offset) {
					if (streamClosed) {
						throw NativeException(className, "skip", SOCKET_EXCEPTION, "Socket Input Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "skip", SOCKET_EXCEPTION, "Socket is closed");
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

				jlong WindowsSocketInputStream::available() {
					if (streamClosed) {
						throw NativeException(className, "available", SOCKET_EXCEPTION, "Socket Input Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "available", SOCKET_EXCEPTION, "Socket is closed");
					}
					u_long availableBytes = 0;
					if (ioctlsocket(socket, FIONREAD, &availableBytes) == SOCKET_ERROR) {
						WindowsUtils::handleLastWinSockError(className, "available", "Failed to get the available bytes to read from the socket!");
					}
					return (jlong) availableBytes;
				}

				void WindowsSocketInputStream::close() {
					if (streamClosed || socketClosed) {
						return;
					}
					if (shutdown(socket, SD_RECEIVE) == SOCKET_ERROR) {
						WindowsUtils::handleLastWinSockError(className, "close", "Failed to close the input stream of the socket!");
					}
					streamClosed = true;
				}

				void WindowsSocketInputStream::markSocketClosed() {
					socketClosed = true;
				}

				jbool WindowsSocketInputStream::isStreamClosed() {
					return streamClosed;
				}

				jint WindowsSocketInputStream::getSoTimeout() {
					return timeout;
				}

				void WindowsSocketInputStream::setSoTimeout(jint timeoutValue) {
					timeout = timeoutValue;
				}

			}
		}
	}
}
