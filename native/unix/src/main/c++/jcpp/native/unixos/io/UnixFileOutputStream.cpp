#include "jcpp/native/unixos/io/UnixFileOutputStream.h"
#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/api/NativeException.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				NativeString UnixFileOutputStream::className("jcpp::native::unixos::io::UnixFileOutputStream");

				UnixFileOutputStream::UnixFileOutputStream(const NativeString& path, jbool append) :
						fileDescriptor() {

					int fd = 0;
					EINTR_RETRY_R(fd, open(path.getString().c_str(), O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)))

					if (fd == -1) {
						switch (errno) {
							case EACCES:
								throw NativeException(className, "UnixFileOutputStream", FILE_ACCESS_DENIED_EXCEPTION, "Access denied", errno);
							case EISDIR:
								throw NativeException(className, "UnixFileOutputStream", FILE_OPEN_EXCEPTION, "The file is a directory", errno);
							case EMFILE:
								throw NativeException(className, "UnixFileOutputStream", FILE_OPEN_EXCEPTION, "Too many open files", errno);
							case ENOENT:
								throw NativeException(className, "UnixFileOutputStream", FILE_NOT_FOUND_EXCEPTION, "File does not exist", errno);
							case ENOSPC:
								throw NativeException(className, "UnixFileOutputStream", FILE_OPEN_EXCEPTION, "No space left on device", errno);
							default:
								throw NativeException(className, "UnixFileOutputStream", FILE_OPEN_EXCEPTION, "Failed to open file", errno);
						}
					}
					fileDescriptor.setDescriptor(fd);
				}

				UnixFileOutputStream::UnixFileOutputStream(const UnixFileDescriptor& fileDescriptor) :
						fileDescriptor(fileDescriptor) {
				}

				UnixFileOutputStream::~UnixFileOutputStream() {
					try {
						close();
					} catch (...) {
					}
				}

				NativeFileDescriptor * UnixFileOutputStream::getNativeFileDescriptor() {
					return &fileDescriptor;
				}

				void UnixFileOutputStream::write(jbyte byte) {
					write(&byte, 0, 1);
				}

				void UnixFileOutputStream::write(jbyte * buf, jint offset, jint length) {
					if (fileDescriptor.getDescriptor() == -1) {
						throw NativeException(className, "read", IO_EXCEPTION, "The file stream was closed!");
					}
					ssize_t written = 0;
					jint writeOffset = 0;
					while (length > 0) {
						written = ::write(fileDescriptor.getDescriptor(), (buf + offset + writeOffset), length);
						if (written == -1) {
							switch (errno) {
								case EINTR:
									continue;
								case EFBIG:
									throw NativeException(className, "write", IO_EXCEPTION, "The size of the file would become larger than the implementation can support.");
								case ENOSPC:
									throw NativeException(className, "write", IO_EXCEPTION, "The device containing the file is full.");
								default:
									throw NativeException(className, "write", IO_EXCEPTION, "Write Error");
							}
						}
						length -= written;
						writeOffset += written;
					}
				}

				void UnixFileOutputStream::flush() {
					if (fileDescriptor.getDescriptor() == -1) {
						throw NativeException(className, "read", IO_EXCEPTION, "The file stream was closed!");
					}
					fsync(fileDescriptor.getDescriptor());
				}

				void UnixFileOutputStream::close() {
					if (fileDescriptor.getDescriptor() != -1) {

						EINTR_RETRY(::close(fileDescriptor.getDescriptor()))

						if (result == -1) {
							switch (errno) {
								case EBADF:
									throw NativeException(className, "UnixFileInputStream", ILLEGAL_ARGUMENT_EXCEPTION, "Bad file descriptor", errno);
								default:
									throw NativeException(className, "UnixFileInputStream", IO_EXCEPTION, "Failed to close file", errno);
							}
						}
						fileDescriptor.setDescriptor(-1);
					}
				}

			}
		}
	}
}
