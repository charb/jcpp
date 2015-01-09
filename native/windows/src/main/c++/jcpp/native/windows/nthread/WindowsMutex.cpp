#include "jcpp/native/windows/nthread/WindowsMutex.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/windows/WindowsUtils.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				NativeString WindowsMutex::className("jcpp::native::windows::thread::WindowsMutex");

				WindowsMutex::WindowsMutex() {
					InitializeCriticalSectionAndSpinCount(&_cs, 4000);
				}

				WindowsMutex::~WindowsMutex() {
					DeleteCriticalSection(&_cs);
				}

				void WindowsMutex::lock() {
					try {
						EnterCriticalSection(&_cs);
						if(listener != null) {
							listener->mutexLocked(this);
						}
					} catch (...) {
						throw NativeException(className, "lock", SYSTEM_EXCEPTION, "Cannot lock mutex!");
					}
				}

				jbool WindowsMutex::tryLock() {
					try {
						jbool locked = TryEnterCriticalSection(&_cs) != 0;
						if((listener != null) && locked) {
							listener->mutexLocked(this);
						}
						return locked;
					} catch (...) {
						throw NativeException(className, "tryLock", SYSTEM_EXCEPTION, "Cannot lock mutex!");
					}
				}

				jbool WindowsMutex::tryLock(jlong milliseconds) {
					jlong startTime = WindowsUtils::getCurrentTimeMillis();
					while ((WindowsUtils::getCurrentTimeMillis() - startTime) < milliseconds) {
						if (tryLock()) {
							return true;
						}
						Sleep(5);
					}
					return false;
				}

				void WindowsMutex::unlock() {
					if(listener != null) {
						listener->mutexUnlock(this);
					}
					LeaveCriticalSection(&_cs);
				}
			}
		}
	}
}

