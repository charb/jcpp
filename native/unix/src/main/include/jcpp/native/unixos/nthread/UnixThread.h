#ifndef JCPP_NATIVE_UNIXOS_THREAD_UNIXTHREAD
#define JCPP_NATIVE_UNIXOS_THREAD_UNIXTHREAD

#include "jcpp/native/unixos/nthread/UnixAbstractThread.h"
#include "jcpp/native/api/nthread/NativeStackTraceElement.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				class JCPP_EXPORT UnixThread: public UnixAbstractThread {

				private:
					static NativeString className;

					static UnixMutex uniqueIdMutex;
					static jlong currenId;

					jlong id;

					UnixMutex joinMutex;
					UnixMutex doneMutex;
					UnixMutex runningMutex;
					jbool running;

					jbool started;
					UnixMutex methodStartedMutex;
					jbool methodStarted;


					static jlong uniqueId();
					static void* runnableEntry(void* pThread);

				public:
					UnixThread(NativeRunnable * runnable);
					virtual ~UnixThread();

					virtual jlong getId() const;

					virtual void start();

					virtual void join();
					virtual jbool join(jlong milliseconds);

					virtual jbool isRunning();

					virtual void sleep(jlong milliseconds);

				};

			}
		}
	}
}

#endif

