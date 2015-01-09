#ifndef JCPP_NATIVE_WINDOWS_THREAD_WINDOWSABSTRACTTHREAD
#define JCPP_NATIVE_WINDOWS_THREAD_WINDOWSABSTRACTTHREAD

#include "jcpp/native/api/nthread/NativeThread.h"
#include "jcpp/native/windows/nthread/WindowsMutex.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

			class JCPP_EXPORT WindowsAbstractThread : public NativeThread {

			private:
				static NativeString className;

			protected:
				NativeString name;
				WindowsMutex mutex;

				Priority priority;
				HANDLE thread;

			public:
				WindowsAbstractThread(NativeRunnable * runnable);

				virtual jlong getId() const = 0;
				virtual NativeString getName();
				virtual void setName(NativeString& name);

				virtual Priority getPriority();
				virtual void setPriority(Priority priority) = 0;

				virtual void start() = 0;

				virtual void join() = 0;
				virtual jbool join(jlong milliseconds) = 0;

				virtual jbool isRunning() = 0;

				virtual void sleep(jlong milliseconds);
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
