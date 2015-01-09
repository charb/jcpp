#ifndef JCPP_NATIVE_WINDOWS_THREAD_WINDOWSCONDITION
#define JCPP_NATIVE_WINDOWS_THREAD_WINDOWSCONDITION

#include "jcpp/native/api/nthread/NativeCondition.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/windows/WindowsInclude.h"
#include "jcpp/native/windows/nthread/WindowsMutex.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				class JCPP_EXPORT WindowsCondition: public NativeCondition, public NativeMutexListener {

				private:
					static NativeString className;

					WindowsMutex * mutex;
					HANDLE owner;
					jlong lockCount;      // Number of times the mutex is locked

					HANDLE wait_event;    // Manual-reset event for notifications
					jlong counter;        // Current number of notifications
					jlong waiters;        // Number of threads waiting for notification
					jlong tickets;        // Number of waiters to be notified

					bool ownedBySelf();

					WindowsCondition(const WindowsCondition&);
					WindowsCondition& operator =(const WindowsCondition&);

				public:
					WindowsCondition(WindowsMutex * mutex);
					virtual ~WindowsCondition();

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
