#ifndef JCPP_NATIVE_UNIXOS_THREAD_UNIXMONITOR
#define JCPP_NATIVE_UNIXOS_THREAD_UNIXMONITOR

#include "jcpp/native/api/nthread/NativeCondition.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"
#include <pthread.h>

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				class JCPP_EXPORT UnixCondition: public NativeCondition, public NativeMutexListener {

				private:
					static NativeString className;

					UnixMutex * mutex;
					pthread_t owner;
					jlong lockCount;      // Number of times the mutex is locked

					pthread_cond_t cond;
					jbool ownerValid;
					jlong counter;        // Current number of notifications
					jlong waiters;        // Number of threads waiting for notification
					jlong tickets;        // Number of waiters to be notified

					UnixCondition(const UnixCondition&);
					UnixCondition& operator =(const UnixCondition&);

				public:
					UnixCondition(UnixMutex * mutex);
					virtual ~UnixCondition();

					virtual NativeMutex * getMutex();

					virtual jbool wait(jlong timeout = 0);
					virtual jbool notify();
					virtual jbool notifyAll();

					virtual void mutexLocked(NativeMutex * mutex);
					virtual void mutexUnlock(NativeMutex * mutex);

				};

			}
		}
	}

}

#endif
