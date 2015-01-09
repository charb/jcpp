#include "jcpp/native/unixos/net/UnixSocketOutputStream.h"
#include "jcpp/native/api/NativeException.h"

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				NativeString UnixSocketOutputStream::className("jcpp::native::unixos::net::UnixSocketOutputStream");

				UnixSocketOutputStream::UnixSocketOutputStream(int socket) :
						socket(socket), streamClosed(false), socketClosed(false) {
				}

				UnixSocketOutputStream::~UnixSocketOutputStream() {
				}

				void UnixSocketOutputStream::write(jbyte byte) {
					write(&byte, 0, 1);
				}

				void UnixSocketOutputStream::write(jbyte * buf, jint offset, jint len) {
					if (streamClosed) {
						throw NativeException(className, "write", IO_EXCEPTION, "Socket Output Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "write", IO_EXCEPTION, "Socket is closed");
					}

					int sentData = 0;
					int sendOffset = 0;

					while (len > 0) {

						int chunck = len;

						while (chunck > 0) {
							sentData = send(socket, (const char *) (buf + offset + sendOffset), chunck, 0);
							if (sentData == -1) {
								if ((errno == EMSGSIZE) && (chunck > 65536)) {
									chunck = 65536;
									continue;
								} else if (errno == EINTR) {
									continue;
								}
								UnixUtils::handleLastSocketError(className, "write", "Failed to write into the socket output stream!");
							}
							chunck -= sentData;
							len -= sentData;
							sendOffset += sentData;
						}
					}

				}

				void UnixSocketOutputStream::flush() {
					if (streamClosed) {
						throw NativeException(className, "write", IO_EXCEPTION, "Socket Output Stream is closed");
					}
					if (socketClosed) {
						throw NativeException(className, "write", IO_EXCEPTION, "Socket is closed");
					}
				}

				void UnixSocketOutputStream::close() {
					if (streamClosed || socketClosed) {
						return;
					}
					if (shutdown(socket, SHUT_WR) == -1) {
						UnixUtils::handleLastSocketError(className, "close", "Failed to close the output stream of the socket!");
					}
					streamClosed = true;
				}

				void UnixSocketOutputStream::markSocketClosed() {
					socketClosed = true;
				}

				bool UnixSocketOutputStream::isStreamClosed() {
					return streamClosed;
				}

			}
		}
	}
}
