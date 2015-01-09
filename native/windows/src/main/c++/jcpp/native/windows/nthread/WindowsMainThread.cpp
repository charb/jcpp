#include "jcpp/native/windows/nthread/WindowsMainThread.h"
#include "jcpp/native/api/NativeException.h"

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				NativeString WindowsMainThread::className("jcpp::native::windows::thread::WindowsMainThread");
				WindowsMainThread WindowsMainThread::instance;

				WindowsMainThread::WindowsMainThread() :
						WindowsAbstractThread(null) {

					name = "Main Thread";
					thread = GetCurrentThread();
					state = NTH_RUNNABLE;
				}

				WindowsMainThread::~WindowsMainThread() {
					CloseHandle(thread);
					thread = null;
				}

				WindowsMainThread * WindowsMainThread::getInstance() {
					return &instance;
				}

				int WindowsMainThread::priorityToNativePriority() {
					switch (priority) {
						case LOWEST:
							return THREAD_PRIORITY_LOWEST;
						case LOW:
							return THREAD_PRIORITY_BELOW_NORMAL;
						case NORMAL:
							return THREAD_PRIORITY_NORMAL;
						case HIGH:
							return THREAD_PRIORITY_ABOVE_NORMAL;
						case HIGHEST:
							return THREAD_PRIORITY_HIGHEST;
					}
					return THREAD_PRIORITY_NORMAL;
				}

				jlong WindowsMainThread::getId() const {
					return 0;
				}

				void WindowsMainThread::setPriority(Priority newPriority) {
					ScopedLock synchronize(mutex);
					if (priority != newPriority) {
						priority = newPriority;
						if (thread) {
							if (SetThreadPriority(thread, priorityToNativePriority()) == 0) {
								throw NativeException(className, "setPriority", SYSTEM_EXCEPTION, "cannot set thread priority");
							}
						}
					}
				}

				void WindowsMainThread::start() {
					throw NativeException(className, "start", SYSTEM_EXCEPTION, "Main Thread is already Running");
				}

				void WindowsMainThread::join() {
					throw NativeException(className, "join", SYSTEM_EXCEPTION, "Cannot join the main thread");
				}

				jbool WindowsMainThread::join(jlong milliseconds) {
					throw NativeException(className, "join", SYSTEM_EXCEPTION, "Cannot join the main thread");
				}

				jbool WindowsMainThread::isRunning() {
					return true;
				}

			}
		}
	}
}

