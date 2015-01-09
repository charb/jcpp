#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/unixos/io/UnixFileInputStream.h"
#include "jcpp/native/api/NativeException.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <termios.h>

#if defined(SOLARIS2)
#include <sys/filio.h>
#elif defined(Linux)
#include <sys/ioctl.h>
#endif

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				NativeString UnixFileInputStream::className("jcpp::native::unixos::io::UnixFileInputStream");

				UnixFileInputStream::UnixFileInputStream(const NativeString& path) :
						fileDescriptor() {
					int fd = 0;
					EINTR_RETRY_R(fd, open(path.getString().c_str(), O_RDONLY))

					if (fd == -1) {
						switch (errno) {
							case EACCES:
								throw NativeException(className, "UnixFileInputStream", FILE_ACCESS_DENIED_EXCEPTION, "Access denied", errno);
							case EISDIR:
								throw NativeException(className, "UnixFileInputStream", FILE_OPEN_EXCEPTION, "The file is a directory", errno);
							case EMFILE:
								throw NativeException(className, "UnixFileInputStream", FILE_OPEN_EXCEPTION, "Too many open files", errno);
							case ENOENT:
								throw NativeException(className, "UnixFileInputStream", FILE_NOT_FOUND_EXCEPTION, "File does not exist", errno);
							case ENOSPC:
								throw NativeException(className, "UnixFileInputStream", FILE_OPEN_EXCEPTION, "No space left on device", errno);
							default:
								throw NativeException(className, "UnixFileInputStream", FILE_OPEN_EXCEPTION, "Failed to open file", errno);
						}
					}
					fileDescriptor.setDescriptor(fd);
				}

				UnixFileInputStream::UnixFileInputStream(const UnixFileDescriptor& fileDescriptor) :
						fileDescriptor(fileDescriptor) {
				}

				UnixFileInputStream::~UnixFileInputStream() {
					try {
						close();
					} catch (...) {
					}
				}

				NativeFileDescriptor * UnixFileInputStream::getNativeFileDescriptor() {
					return &fileDescriptor;
				}

				jbyte UnixFileInputStream::read() {
					jbyte byte;
					jint n = read(&byte, 0, 1);
					if (n == 0) {
						return -1;
					}
					return byte;
				}

				jint UnixFileInputStream::read(jbyte * buf, jint offset, jint length) {
					if (fileDescriptor.getDescriptor() == -1) {
						throw NativeException(className, "read", IO_EXCEPTION, "The file stream was closed!");
					}

					ssize_t n = 0;
					EINTR_RETRY_R(n, ::read(fileDescriptor.getDescriptor(), (buf + offset), length));

					if (n == -1) {
						switch (errno) {
							case EBADF:
								throw NativeException(className, "read", IO_EXCEPTION, "Bad file descriptor");
							default:
								throw NativeException(className, "read", IO_EXCEPTION, "Read Error");
						}
					} else if (n == 0) {
						return -1;
					}
					return n;
				}

				jlong UnixFileInputStream::skip(jlong offset) {
					if (fileDescriptor.getDescriptor() == -1) {
						throw NativeException(className, "skip", IO_EXCEPTION, "The file stream was closed!");
					}

					off_t currentPosition = lseek(fileDescriptor.getDescriptor(), 0, SEEK_CUR);
					if (currentPosition == -1) {
						throw NativeException(className, "skip", IO_EXCEPTION, "Failed to skip");
					}
					off_t newPosition = lseek(fileDescriptor.getDescriptor(), offset, SEEK_CUR);
					if (newPosition == -1) {
						throw NativeException(className, "skip", IO_EXCEPTION, "Failed to skip");
					}

					return newPosition - currentPosition;
				}

				jlong UnixFileInputStream::available() {
					if (fileDescriptor.getDescriptor() == -1) {
						throw NativeException(className, "skip", IO_EXCEPTION, "The file stream was closed!");
					}
					int n = -1;
					if (ioctl(fileDescriptor.getDescriptor(), FIONREAD, &n) < 0) {
						return -1;
					}
					return n;
				}

				void UnixFileInputStream::close() {
					if (fileDescriptor.getDescriptor() != -1) {

						EINTR_RETRY(::close(fileDescriptor.getDescriptor()))

						if (result == -1) {
							switch (errno) {
								case EBADF:
									throw NativeException(className, "close", IO_EXCEPTION, "Bad file descriptor", errno);
								default:
									throw NativeException(className, "close", IO_EXCEPTION, "Failed to close file", errno);
							}
						}
						fileDescriptor.setDescriptor(-1);
					}
				}

			}
		}
	}
}
