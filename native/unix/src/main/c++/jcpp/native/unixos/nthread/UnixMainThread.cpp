#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/unixos/nthread/UnixMainThread.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/api/nthread/ScopedLock.h"
#include <errno.h>

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				NativeString UnixMainThread::className("jcpp::native::unixos::thread::UnixMainThread");
				UnixMainThread UnixMainThread::instance;

				UnixMainThread::UnixMainThread() :
						UnixAbstractThread(null) {
					state = NTH_RUNNABLE;
					name = "Main Thread";
#if defined(SOLARIS2)
					thread = thr_self();
#else
					thread = pthread_self();
#endif
				}

				UnixMainThread::~UnixMainThread() {
				}

				UnixMainThread * UnixMainThread::getInstance() {
					return &instance;
				}


				jlong UnixMainThread::getId() const {
					return 0;
				}

				void UnixMainThread::start() {
					throw NativeException(className, "start", SYSTEM_EXCEPTION, "Main Thread is already Running");
				}

				void UnixMainThread::join() {
					throw NativeException(className, "join", SYSTEM_EXCEPTION, "Cannot join the main thread");
				}

				jbool UnixMainThread::join(jlong milliseconds) {
					throw NativeException(className, "join", SYSTEM_EXCEPTION, "Cannot join the main thread");
				}

				jbool UnixMainThread::isRunning() {
					return true;
				}

				void UnixMainThread::sleep(jlong milliseconds) {
					int rc;
					do {
						struct timespec ts;
						struct timespec tsRem;
						UnixUtils::longToTimespec(ts, milliseconds);
						rc = nanosleep(&ts, &tsRem);

						if (rc < 0 && errno == EINTR) {
							milliseconds = UnixUtils::timespecToLong(tsRem);
						}
					} while (milliseconds > 0 && rc < 0 && errno == EINTR);
					if (rc < 0 && milliseconds > 0)
						throw NativeException(className, "sleep", SYSTEM_EXCEPTION, "Failed to Sleep");
				}

			}
		}
	}
}

