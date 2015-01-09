#include "jcpp/native/windows/io/WindowsFileDescriptor.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				WindowsFileDescriptor::WindowsFileDescriptor() :
						handle(null) {
				}

				WindowsFileDescriptor::WindowsFileDescriptor(HANDLE handle) :
						handle(handle) {
				}

				WindowsFileDescriptor::~WindowsFileDescriptor() {
				}

				void WindowsFileDescriptor::setHandle(HANDLE newHandle) {
					handle = newHandle;
				}

				HANDLE WindowsFileDescriptor::getHandle() {
					return handle;
				}

			}
		}
	}
}

