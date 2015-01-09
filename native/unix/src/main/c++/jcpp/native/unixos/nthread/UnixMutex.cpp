#include "jcpp/native/unixos/nthread/UnixMutex.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/unixos/UnixUtils.h"
#include <pthread.h>
#include <errno.h>

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				NativeString UnixMutex::className("jcpp::native::unixos::thread::UnixMutex");

				UnixMutex::UnixMutex() {
					pthread_mutexattr_t attr;
					pthread_mutexattr_init(&attr);
					pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
					if (pthread_mutex_init(&_mutex, &attr)) {
						pthread_mutexattr_destroy(&attr);
						throw NativeException(className, "UnixMutex", SYSTEM_EXCEPTION, "Cannot create mutex!");
					}
					pthread_mutexattr_destroy(&attr);
				}

				UnixMutex::~UnixMutex() {
					pthread_mutex_destroy(&_mutex);
				}

				pthread_mutex_t * UnixMutex::getPthreadMutex() {
					return &_mutex;
				}

				void UnixMutex::lock() {
					if (pthread_mutex_lock(&_mutex) != 0) {
						throw NativeException(className, "lock", SYSTEM_EXCEPTION, "Cannot lock mutex!");
					}
					if (listener != null) {
						listener->mutexLocked(this);
					}
				}

				jbool UnixMutex::tryLock() {
					int rc = pthread_mutex_trylock(&_mutex);
					if (rc == 0) {
						if (listener != null) {
							listener->mutexLocked(this);
						}
						return true;
					} else if (rc == EBUSY) {
						return false;
					} else {
						throw NativeException(className, "tryLock", SYSTEM_EXCEPTION, "Cannot lock mutex!");
					}
				}

				jbool UnixMutex::tryLock(jlong milliseconds) {
					jlong startTime = UnixUtils::getCurrentTimeMillis();
					while ((UnixUtils::getCurrentTimeMillis() - startTime) < milliseconds) {
						if (tryLock()) {
							return true;
						}
						struct timeval tv;
						tv.tv_sec = 0;
						tv.tv_usec = 5 * 1000;
						select(0, NULL, NULL, NULL, &tv);
					}
					return false;
				}

				void UnixMutex::unlock() {
					if (listener != null) {
						listener->mutexUnlock(this);
					}
					if (pthread_mutex_unlock(&_mutex) != 0) {
						throw NativeException(className, "unlock", SYSTEM_EXCEPTION, "Cannot unlock mutex!");
					}
				}

			}
		}
	}
}
