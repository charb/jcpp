#include "jcpp/native/unixos/io/UnixStandardOutputStream.h"
#include "jcpp/native/api/NativeException.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				NativeString UnixStandardOutputStream::className("jcpp::native::unixos::io::UnixStandardOutputStream");

				UnixStandardOutputStream::UnixStandardOutputStream(jbool out) {
					stdFD = out ? STDOUT_FILENO : STDERR_FILENO;
				}

				UnixStandardOutputStream::~UnixStandardOutputStream() {
				}

				void UnixStandardOutputStream::write(jbyte byte) {
					write(&byte, 0, 1);
				}

				void UnixStandardOutputStream::write(jbyte * buf, jint offset, jint length) {
					ssize_t written = 0;
					jint writeOffset = 0;
					while (length > 0) {
						written = ::write(stdFD, (buf + offset + writeOffset), length);
						if (written == -1) {
							switch (errno) {
								case EINTR:
									continue;
								case EFBIG:
									throw NativeException(className, "write", IO_EXCEPTION, "The size of the file would become larger than the implementation can support.", errno);
								case ENOSPC:
									throw NativeException(className, "write", IO_EXCEPTION, "The device containing the file is full.", errno);
								default:
									throw NativeException(className, "write", IO_EXCEPTION, "Write Error", errno);
							}
						}
						length -= written;
						writeOffset += written;
					}
				}

				void UnixStandardOutputStream::flush() {
					fsync(stdFD);
				}

				void UnixStandardOutputStream::close() {
					throw NativeException(className, "close", IO_EXCEPTION, "Should not close Standard Output / Error Streams!");
				}

			}
		}
	}
}
