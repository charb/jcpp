#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/unixos/io/UnixStandardInputStream.h"
#include "jcpp/native/api/NativeException.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {
				NativeString UnixStandardInputStream::className("jcpp::native::unixos::io::UnixStandardInputStream");

				UnixStandardInputStream::UnixStandardInputStream() {
				}

				UnixStandardInputStream::~UnixStandardInputStream() {
				}

				jbyte UnixStandardInputStream::read() {
					jbyte byte = 0;
					jint n = read(&byte, 0, 1);
					if (n == 0) {
						return -1;
					}
					return byte;
				}

				jint UnixStandardInputStream::read(jbyte * buf, jint offset, jint length) {
					ssize_t n = 0;
					EINTR_RETRY_R(n, ::read(STDIN_FILENO, (buf + offset), length))

					if (n == -1) {
						switch (errno) {
							case EBADF:
								throw NativeException(className, "read", IO_EXCEPTION, "Bad file descriptor", errno);
							default:
								throw NativeException(className, "read", IO_EXCEPTION, "Read Error", errno);
						}
					}
					return n;
				}

				jlong UnixStandardInputStream::skip(jlong offset) {
					return 0;
				}

				jlong UnixStandardInputStream::available() {
					return 0;
				}

				void UnixStandardInputStream::close() {
					throw NativeException(className, "close", IO_EXCEPTION, "Should not close Standard Input Stream!");
				}

			}
		}
	}

}
