#include "jcpp/native/windows/nthread/WindowsThreadPointerStorage.h"
#include "jcpp/native/api/NativeException.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				NativeString WindowsThreadPointerStorage::className("jcpp::native::windows::thread::WindowsThreadPointerStorage");
				WindowsThreadPointerStorage WindowsThreadPointerStorage::instance;

				WindowsThreadPointerStorage::WindowsThreadPointerStorage() :
						slot(TlsAlloc()) {
					if (slot == TLS_OUT_OF_INDEXES) {
						throw NativeException(className, "WindowsThreadPointerStorage()", SYSTEM_EXCEPTION, "cannot allocate thread context key");
					}
				}

				WindowsThreadPointerStorage::~WindowsThreadPointerStorage() {
					TlsFree(slot);
				}

				WindowsThreadPointerStorage* WindowsThreadPointerStorage::getInstance() {
					return &instance;
				}

				WindowsThread * WindowsThreadPointerStorage::get() const {
					return reinterpret_cast<WindowsThread*>(TlsGetValue(slot));
				}

				void WindowsThreadPointerStorage::set(WindowsThread * pthread) {
					TlsSetValue(slot, pthread);
				}

			}
		}
	}
}

