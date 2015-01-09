#ifndef JCPP_NATIVE_UNIXOS_THREAD_UNIXABSTRACTTHREAD
#define JCPP_NATIVE_UNIXOS_THREAD_UNIXABSTRACTTHREAD

#include "jcpp/native/api/nthread/NativeThread.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"

#if defined(SOLARIS2)
#include <thread.h>
#else
#include <pthread.h>
#endif

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

			class JCPP_EXPORT UnixAbstractThread: public NativeThread {

			private:
				static NativeString className;

			protected:
				NativeString name;
				UnixMutex mutex;

				Priority priority;
#if defined(SOLARIS2)
				thread_t thread;
#else
				pthread_t thread;
#endif

				int priorityToNativePriority();

			public:
				UnixAbstractThread(NativeRunnable * runnable);


				virtual jlong getId() const = 0;
				virtual NativeString getName();
				virtual void setName(NativeString& name);

				virtual Priority getPriority();
				virtual void setPriority(Priority priority);

				virtual void start() = 0;

				virtual void join() = 0;
				virtual jbool join(jlong milliseconds) = 0;

				virtual jbool isRunning() = 0;

				virtual void sleep(jlong milliseconds) = 0;
				virtual void yield();

				virtual void suspend();
				virtual void resume();

				virtual void getStackTrace(std::vector<NativeStackTraceElement> &stackTrace);

			};

			}
		}
	}
}

#endif
