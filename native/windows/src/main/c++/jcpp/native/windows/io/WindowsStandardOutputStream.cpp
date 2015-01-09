#include "jcpp/native/windows/io/WindowsStandardOutputStream.h"
#include "jcpp/native/api/NativeException.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				NativeString WindowsStandardOutputStream::className("jcpp::native::windows::io::WindowsStandardOutputStream");

				WindowsStandardOutputStream::WindowsStandardOutputStream(jbool out) {
					stdHandle = GetStdHandle(out ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE);
					if (stdHandle == INVALID_HANDLE_VALUE) {
						throw NativeException(className, "WindowsStandardOutputStream", IO_EXCEPTION, out ? "Failed to Get Standard Output Handle" : "Failed to Get Standard Error Handle");
					}
				}

				WindowsStandardOutputStream::~WindowsStandardOutputStream() {
				}

				void WindowsStandardOutputStream::write(jbyte byte) {
					write(&byte, 0, 1);
				}

				void WindowsStandardOutputStream::write(jbyte * buf, jint offset, jint length) {
					DWORD written = 0;
					jint writeOffset = 0;
					while (length > 0) {
						if (WriteFile(stdHandle, (buf + offset + writeOffset), length, &written, NULL) == 0) {
							throw NativeException(className, "write", IO_EXCEPTION, "Write Error");
						}
						length -= written;
						writeOffset += written;
					}
				}

				void WindowsStandardOutputStream::flush() {
				}

				void WindowsStandardOutputStream::close() {
					throw NativeException(className, "close", IO_EXCEPTION, "Should not close Standard Output / Error Streams!");
				}

			}
		}
	}
}
