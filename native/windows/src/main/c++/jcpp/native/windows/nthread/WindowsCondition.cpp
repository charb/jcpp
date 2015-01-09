#include "jcpp/native/windows/nthread/WindowsCondition.h"
#include "jcpp/native/api/NativeException.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				NativeString WindowsCondition::className("jcpp::native::windows::thread::WindowsMonitor");

				WindowsCondition::WindowsCondition(WindowsMutex * mutex) :
						NativeCondition(), mutex(mutex) {
					owner = NULL;
					lockCount = 0;

					wait_event = CreateEvent(NULL, true, false, NULL);
					if (wait_event == NULL) {
						throw NativeException(className, "WindowsMonitor", ILLEGAL_STATE_EXCEPTION, "Failed to create an Event!");
					}
					counter = 0;
					tickets = 0;
					waiters = 0;
					mutex->setListener(this);
				}

				WindowsCondition::~WindowsCondition() {
					mutex->setListener(null);
					mutex = null;
					if (owner != NULL) {
						throw NativeException(className, "~WindowsMonitor", ILLEGAL_STATE_EXCEPTION, "Deleting an owned monitor!");
					}
					CloseHandle(wait_event);
				}

				NativeMutex * WindowsCondition::getMutex() {
					return mutex;
				}

				void WindowsCondition::mutexLocked(NativeMutex * lockedMutex) {
					if(mutex == lockedMutex) {
						if(lockCount++ == 0) {
							owner = GetCurrentThread();
						}
					}
				}

				void WindowsCondition::mutexUnlock(NativeMutex * unlockedMutex) {
					if(mutex == unlockedMutex) {
						if(--lockCount <= 0) {
							if(lockCount < 0) {
								lockCount = 0;
							} else {
								owner = NULL;
							}
						}
					}
				}

				jbool WindowsCondition::wait(jlong timeout) {
					if (!ownedBySelf()) {
						throw NativeException(className, "wait", ILLEGAL_STATE_EXCEPTION, "Current thread does not own the lock!");
					}

					// 0 means forever. Convert to Windows specific code.
					DWORD timeout_value = (timeout == 0) ? INFINITE : timeout;
					DWORD which;

					jlong c = counter;
					bool retry = false;

					waiters++;
					// Loop until condition variable is signaled.  The event object is
					// set whenever the condition variable is signaled, and tickets will
					// reflect the number of threads which have been notified. The counter
					// field is used to make sure we don't respond to notifications that
					// have occurred *before* we started waiting, and is incremented each
					// time the condition variable is signaled.

					while (true) {

						// Leave critical region
						int currentLockCount = lockCount;
						for(int i = 0; i < currentLockCount; i++) {
							mutex->unlock();
						}

						// If this is a retry, let other low-priority threads have a chance
						// to run.  Make sure that we sleep outside of the critical section.
						if (retry) {
							Sleep(1);
						} else {
							retry = true;
						}

						which = WaitForSingleObject(wait_event, timeout_value);
						// Enter critical section

						for(int i = 0; i < currentLockCount; i++) {
							mutex->lock();
						}

						if (tickets != 0 && counter != c)
							break;

						if (which == WAIT_TIMEOUT) {
							--waiters;
							return false;
						}
					}
					waiters--;

					// If this was the last thread to be notified, then we need to reset
					// the event object.
					if (--tickets == 0) {
						ResetEvent(wait_event);
					}

					return true;
				}

				jbool WindowsCondition::notify() {
					if (!ownedBySelf()) {
						throw NativeException(className, "notify", ILLEGAL_STATE_EXCEPTION, "Current thread does not own the lock!");
					}

					if (waiters > tickets) {
						if (!SetEvent(wait_event)) {
							return false;
						}
						tickets++;
						counter++;
					}
					return true;
				}

				jbool WindowsCondition::notifyAll() {
					if (!ownedBySelf()) {
						throw NativeException(className, "notifyAll", ILLEGAL_STATE_EXCEPTION, "Current thread does not own the lock!");
					}

					if (waiters > 0) {
						if (!SetEvent(wait_event)) {
							return false;
						}
						tickets = waiters;
						counter++;
					}
					return true;
				}

				bool WindowsCondition::ownedBySelf() {
					return (owner == GetCurrentThread());
				}

			}
		}
	}

}
