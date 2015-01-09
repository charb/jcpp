#include "jcpp/native/unixos/nthread/UnixCondition.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/unixos/UnixUtils.h"
#include <errno.h>

#include <stdio.h>

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				NativeString UnixCondition::className("jcpp::native::unixos::thread::UnixCondition");

				UnixCondition::UnixCondition(UnixMutex * mutex) :
						NativeCondition(), mutex(mutex), cond(), owner(), ownerValid(false) {
					lockCount = 0;

					if (pthread_cond_init(&cond, NULL)) {
						throw NativeException(className, "UnixCondition", ILLEGAL_STATE_EXCEPTION, "cannot create a condition!");
					}
					counter = 0;
					tickets = 0;
					waiters = 0;
					mutex->setListener(this);
				}

				UnixCondition::~UnixCondition() {
					mutex->setListener(null);
					mutex = null;
					if (ownerValid) {
						throw NativeException(className, "~UnixCondition", ILLEGAL_STATE_EXCEPTION, "Deleting an owned monitor!");
					}
					pthread_cond_destroy(&cond);
				}

				NativeMutex * UnixCondition::getMutex() {
					return mutex;
				}

				void UnixCondition::mutexLocked(NativeMutex * lockedMutex) {
					if (mutex == lockedMutex) {
						if (lockCount++ == 0) {
							owner = pthread_self();
							ownerValid = true;
						}
					}
				}

				void UnixCondition::mutexUnlock(NativeMutex * unlockedMutex) {
					if (mutex == unlockedMutex) {
						if (--lockCount <= 0) {
							if (lockCount < 0) {
								lockCount = 0;
							} else {
								ownerValid = false;
							}
						}
					}
				}

				jbool UnixCondition::wait(jlong timeout) {
					if (!ownerValid || (pthread_equal(owner, pthread_self()) == 0)) {
						throw NativeException(className, "wait", ILLEGAL_STATE_EXCEPTION, "Current thread does not own the lock!");
					}
					jlong c = counter;
					bool retry = false;

					waiters++;

					while (true) {
						if (!retry) {
							retry = true;
						}

						if (timeout == 0) {
							ownerValid = false;

							int currentLockCount = lockCount;
							for (int i = 0; i < currentLockCount - 1; i++) {
								mutex->unlock();
							}

							lockCount = 0;
							ownerValid = false;
							int returnValue = pthread_cond_wait(&cond, mutex->getPthreadMutex());
							lockCount = 1;
							owner = pthread_self();
							ownerValid = true;

							for (int i = 0; i < currentLockCount - 1; i++) {
								mutex->lock();
							}

							if (returnValue != 0) {
								waiters--;
								throw NativeException(className, "wait", SYSTEM_EXCEPTION, "Failed to wait, make sure calling thread holds the lock!");
							}
							if (tickets != 0 && counter != c)
								break;
						} else {
							struct timespec tv;
							struct timeval now;
							gettimeofday(&now,NULL);
							//tv is a timestamp, not a duration, setting value to now+timeout
						    tv.tv_sec = now.tv_sec + timeout / 1000;
						    tv.tv_nsec = now.tv_usec * 1000 + 1000 * 1000 * (timeout % 1000);
						    tv.tv_sec += tv.tv_nsec / (1000 * 1000 * 1000);
						    tv.tv_nsec %= (1000 * 1000 * 1000);

							ownerValid = false;
							int currentLockCount = lockCount;
							for (int i = 0; i < currentLockCount - 1; i++) {
								mutex->unlock();
							}

							lockCount = 0;
							ownerValid = false;
							int returnValue = pthread_cond_timedwait(&cond, mutex->getPthreadMutex(), &tv);
							lockCount = 1;
							owner = pthread_self();
							ownerValid = true;

							for (int i = 0; i < currentLockCount - 1; i++) {
								mutex->lock();
							}

							if ((returnValue != 0) && (returnValue != ETIMEDOUT)) {
								waiters--;
								throw NativeException(className, "wait", SYSTEM_EXCEPTION, "Failed to wait, make sure calling thread holds the lock!");
							}
							if (tickets != 0 && counter != c)
								break;
							if (returnValue == ETIMEDOUT) {
								--waiters;
								return false;
							}
						}
					}

					waiters--;
					--tickets;

					return true;
				}

				jbool UnixCondition::notify() {
					if (!ownerValid || (pthread_equal(owner, pthread_self()) == 0)) {
						throw NativeException(className, "notify", ILLEGAL_STATE_EXCEPTION, "Current thread does not own the lock!");
					}
					if (waiters > tickets) {
						if (pthread_cond_signal(&cond) != 0) {
							return false;
						}
						tickets++;
						counter++;
					}
					return true;
				}

				jbool UnixCondition::notifyAll() {
					if (!ownerValid || (pthread_equal(owner, pthread_self()) == 0)) {
						throw NativeException(className, "notifyAll", ILLEGAL_STATE_EXCEPTION, "Current thread does not own the lock!");
					}
					if (waiters > 0) {
						if (pthread_cond_broadcast(&cond) != 0) {
							return false;
						}
						tickets = waiters;
						counter++;
					}
					return true;
				}

			}
		}
	}

}
