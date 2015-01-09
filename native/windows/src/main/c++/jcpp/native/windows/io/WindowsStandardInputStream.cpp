#include "jcpp/native/windows/io/WindowsStandardInputStream.h"
#include "jcpp/native/api/NativeException.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {
				NativeString WindowsStandardInputStream::className("jcpp::native::windows::io::WindowsStandardInputStream");

				WindowsStandardInputStream::WindowsStandardInputStream() {
					stdHandle = GetStdHandle(STD_INPUT_HANDLE);
					if (stdHandle == INVALID_HANDLE_VALUE) {
						throw NativeException(className, "WindowsStandardInputStream", IO_EXCEPTION, "Failed to Get Standard Input Handle");
					}
				}

				WindowsStandardInputStream::~WindowsStandardInputStream() {
				}

				jbyte WindowsStandardInputStream::read() {
					jbyte byte = 0;
					jint n = read(&byte, 0, 1);
					if (n == 0) {
						return -1;
					}
					return byte;
				}

				jint WindowsStandardInputStream::read(jbyte * buf, jint offset, jint length) {
					DWORD read = 0;
					if (ReadFile(stdHandle, (buf + offset), length, &read, NULL) == 0) {
						int error = GetLastError();
						if (error == ERROR_BROKEN_PIPE) {
							return 0; /* EOF */
						}
						throw NativeException(className, "read", IO_EXCEPTION, "Read Error");
					}
					return read;
				}

				jlong WindowsStandardInputStream::skip(jlong offset) {
					return 0;
				}

				jlong WindowsStandardInputStream::available() {
					return 0;
				}

				void WindowsStandardInputStream::close() {
					throw NativeException(className, "close", IO_EXCEPTION, "Should not close Standard Input Stream!");
				}

			}
		}
	}

}
