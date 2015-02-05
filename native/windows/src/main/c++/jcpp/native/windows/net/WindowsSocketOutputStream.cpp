#include "jcpp/native/windows/net/WindowsSocketOutputStream.h"
#include "jcpp/native/api/NativeException.h"
#include <iostream>

using namespace std;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace net {

				NativeString WindowsSocketOutputStream::className("jcpp::native::windows::net::WindowsSocketOutputStream");

				WindowsSocketOutputStream::WindowsSocketOutputStream(SOCKET socket) :
						socket(socket), streamClosed(false), socketClosed(false) {
				}

				WindowsSocketOutputStream::~WindowsSocketOutputStream() {
				}

				void WindowsSocketOutputStream::write(jbyte byte) {
					write(&byte, 0, 1);
				}

				void WindowsSocketOutputStream::write(jbyte * buf, jint offset, jint len) {
					if (streamClosed) {
						throw NativeException(className, "write", SOCKET_EXCEPTION, "Socket Output Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "write", SOCKET_EXCEPTION, "Socket is closed");
					}

					int sentData = 0;
					int sendOffset = 0;

					while (len > 0) {

						int chunck = len;
						int retry = 0;

						while (chunck > 0) {
							sentData = send(socket, (const char *) (buf + offset + sendOffset), chunck, 0);
							if (sentData == SOCKET_ERROR) {

								/*
								 * Due to a bug in Windows Sockets (observed on NT and Windows
								 * 2000) it may be necessary to retry the send. The issue is that
								 * on blocking sockets send/WSASend is supposed to block if there
								 * is insufficient buffer space available. If there are a large
								 * number of threads blocked on write due to congestion then it's
								 * possile to hit the NT/2000 bug whereby send returns WSAENOBUFS.
								 * The workaround we use is to retry the send. If we have a
								 * large buffer to send (>2k) then we retry with a maximum of
								 * 2k buffer. If we hit the issue with <=2k buffer then we backoff
								 * for 1 second and retry again. We repeat this up to a reasonable
								 * limit before bailing out and throwing an exception. In load
								 * conditions we've observed that the send will succeed after 2-3
								 * attempts but this depends on network buffers associated with
								 * other sockets draining.
								 */

								if (WSAGetLastError() == WSAENOBUFS) {
									if (chunck > 2048) {
										chunck = 2048;
										continue;
									} else if (retry >= 30) {
										throw NativeException(className, "write", IO_EXCEPTION, "No buffer space available - exhausted attempts to queue buffer");
									}
									Sleep(1000);
									retry++;
									continue;
								} else {
									WindowsUtils::handleLastWinSockError(className, "write", "Failed to write into the socket output stream!");
								}
							}
							chunck -= sentData;
							len -= sentData;
							sendOffset += sentData;
						}
					}

				}

				void WindowsSocketOutputStream::flush() {
					if (streamClosed) {
						throw NativeException(className, "write", SOCKET_EXCEPTION, "Socket Output Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "write", SOCKET_EXCEPTION, "Socket is closed");
					}
				}

				void WindowsSocketOutputStream::close() {
					if (streamClosed || socketClosed) {
						return;
					}
					if (shutdown(socket, SD_SEND) == SOCKET_ERROR) {
						WindowsUtils::handleLastWinSockError(className, "close", "Failed to close the output stream of the socket!");
					}
					streamClosed = true;
				}

				void WindowsSocketOutputStream::markSocketClosed() {
					socketClosed = true;
				}

				bool WindowsSocketOutputStream::isStreamClosed() {
					return streamClosed;
				}

			}
		}
	}
}
