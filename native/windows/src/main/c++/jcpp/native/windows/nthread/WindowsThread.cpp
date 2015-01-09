#include "jcpp/native/windows/nthread/WindowsThread.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/windows/WindowsUtils.h"
#include "jcpp/native/windows/nthread/WindowsThreadPointerStorage.h"

#include <process.h>

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				NativeString WindowsThread::className("jcpp::native::windows::thread::WindowsThread");
				WindowsMutex WindowsThread::uniqueIdMutex;
				jlong WindowsThread::currenId = 0;

				WindowsThread::WindowsThread(NativeRunnable * runnable) :
						WindowsAbstractThread(runnable), id(uniqueId()), threadId(0) {
					name += "Thread id=";
					name += id;
				}

				WindowsThread::~WindowsThread() {
					if (!thread) {
						return;
					}
					if (CloseHandle(thread)) {
						thread = 0;
					}
				}

				jlong WindowsThread::uniqueId() {
					ScopedLock synchronize(uniqueIdMutex);
					return ++currenId;
				}

				DWORD WINAPI WindowsThread::runnableEntry(LPVOID pThread) {
					WindowsThread* winThread = reinterpret_cast<WindowsThread*>(pThread);
					WindowsThreadPointerStorage::getInstance()->set(winThread);
					try {
						winThread->state = NTH_RUNNABLE;
						winThread->runnable->run();
					} catch (...) {
						// TODO same than unix thread
					}
					winThread->state = NTH_TERMINATED;
					winThread->storage->clear();

					winThread->runnable = null;

					if(winThread->isDeleteOnFinish()) {
						delete winThread;
					}
					return 0;
				}

				int WindowsThread::priorityToNativePriority() {
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

				jlong WindowsThread::getId() const {
					return id;
				}

				void WindowsThread::setPriority(Priority newPriority) {
					ScopedLock synchronize(mutex);
					if (priority != newPriority) {
						priority = newPriority;
						if (isRunning()) {
							if (SetThreadPriority(thread, priorityToNativePriority()) == 0) {
								throw NativeException(className, "setPriority", SYSTEM_EXCEPTION, "cannot set thread priority");
							}
						}
					}
				}

				void WindowsThread::start() {
					ScopedLock synchronize(mutex);
					if (isRunning()) {
						throw NativeException(className, "start", SYSTEM_EXCEPTION, "thread already running");
					}
					if (runnable == null) {
						throw NativeException(className, "start", ILLEGAL_STATE_EXCEPTION, "Threads can be started one time only!");
					}
					thread = CreateThread(NULL, 0, runnableEntry, this, 0, &threadId);
					if (!thread) {
						runnable = null;
						throw NativeException(className, "start", SYSTEM_EXCEPTION, "Cannot create thread");
					}
					if ((priority != NORMAL) && !SetThreadPriority(thread, priorityToNativePriority()))
						throw NativeException(className, "setPriority", SYSTEM_EXCEPTION, "cannot set thread priority");
				}

				void WindowsThread::join() {
					if (!thread) {
						return;
					}

					switch (WaitForSingleObject(thread, INFINITE)) {
						case WAIT_OBJECT_0:
							return;
						default:
							throw NativeException(className, "join", SYSTEM_EXCEPTION, "cannot join thread");
					}
				}

				jbool WindowsThread::join(jlong milliseconds) {
					if (!thread) {
						return true;
					}

					switch (WaitForSingleObject(thread, milliseconds + 1)) {
						case WAIT_TIMEOUT:
							return false;
						case WAIT_OBJECT_0:
							return true;
						default:
							throw NativeException(className, "join", SYSTEM_EXCEPTION, "cannot join thread");
					}
				}

				jbool WindowsThread::isRunning() {
					if (thread) {
						DWORD ec = 0;
						return GetExitCodeThread(thread, &ec) && ec == STILL_ACTIVE;
					}
					return false;
				}

			}
		}
	}
}

