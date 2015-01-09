#include "jcpp/native/windows/io/WindowsFileOutputStream.h"
#include "jcpp/native/api/NativeException.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				NativeString WindowsFileOutputStream::className("jcpp::native::windows::io::WindowsFileOutputStream");

				WindowsFileOutputStream::WindowsFileOutputStream(const NativeString& path, jbool append) :
						fileDescriptor() {

					const DWORD access = append ? (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA) : GENERIC_WRITE;
					const DWORD disposition = append ? OPEN_ALWAYS : CREATE_ALWAYS;

					HANDLE h = CreateFile(path.getString().c_str(), access, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, disposition, FILE_ATTRIBUTE_NORMAL, NULL);

					if (h == INVALID_HANDLE_VALUE) {
						DWORD err = GetLastError();
						switch (err) {
							case ERROR_TOO_MANY_OPEN_FILES:
								throw NativeException(className, "WindowsFileInputStream", IO_EXCEPTION, "No more file descriptors available (too many open files)", err);
							case ERROR_FILE_NOT_FOUND:
								throw NativeException(className, "WindowsFileInputStream", FILE_NOT_FOUND_EXCEPTION, path, err);
							case ERROR_PATH_NOT_FOUND:
							case ERROR_BAD_NETPATH:
							case ERROR_CANT_RESOLVE_FILENAME:
							case ERROR_INVALID_DRIVE:
								throw NativeException(className, "WindowsFileInputStream", PATH_NOT_FOUND_EXCEPTION, path, err);
							default:
								throw NativeException(className, "WindowsFileInputStream", IO_EXCEPTION, "Failed to open: " + path, err);
						}
					}

					fileDescriptor.setHandle(h);
				}

				WindowsFileOutputStream::WindowsFileOutputStream(const WindowsFileDescriptor& fileDescriptor) :
						fileDescriptor(fileDescriptor) {
				}

				WindowsFileOutputStream::~WindowsFileOutputStream() {
					try {
						close();
					} catch (...) {
					}
				}

				NativeFileDescriptor * WindowsFileOutputStream::getNativeFileDescriptor() {
					return &fileDescriptor;
				}

				void WindowsFileOutputStream::write(jbyte byte) {
					write(&byte, 0, 1);
				}

				void WindowsFileOutputStream::write(jbyte * buf, jint offset, jint length) {
					if (fileDescriptor.getHandle() == null) {
						throw NativeException(className, "write", IO_EXCEPTION, "The file stream was closed!");
					}
					DWORD written = 0;
					jint writeOffset = 0;
					while (length > 0) {
						if (WriteFile(fileDescriptor.getHandle(), (buf + offset + writeOffset), length, &written, NULL) == 0) {
							throw NativeException(className, "write", IO_EXCEPTION, "Write Error");
						}
						length -= written;
						writeOffset += written;
					}
				}

				void WindowsFileOutputStream::flush() {
					if (fileDescriptor.getHandle() == null) {
						throw NativeException(className, "flush", IO_EXCEPTION, "The file stream was closed!");
					}
				}

				void WindowsFileOutputStream::close() {
					HANDLE h = fileDescriptor.getHandle();
					if (h != null && h != INVALID_HANDLE_VALUE) {
						if (CloseHandle(h) == 0) {
							throw NativeException(className, "close", IO_EXCEPTION, "Failed to close handle");
						}
						fileDescriptor.setHandle(null);
					}
				}

			}
		}
	}

}
