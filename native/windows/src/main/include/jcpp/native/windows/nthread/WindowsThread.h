#ifndef JCPP_NATIVE_WINDOWS_THREAD_WINDOWSTHREAD
#define JCPP_NATIVE_WINDOWS_THREAD_WINDOWSTHREAD

#include "jcpp/native/windows/nthread/WindowsAbstractThread.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				class JCPP_EXPORT WindowsThread: public WindowsAbstractThread {

				private:
					static NativeString className;

					static WindowsMutex uniqueIdMutex;
					static jlong currenId;

					jlong id;

					DWORD threadId;

					static jlong uniqueId();
					static DWORD __stdcall runnableEntry(LPVOID pThread);

					int priorityToNativePriority();

				public:
					WindowsThread(NativeRunnable * runnable);
					virtual ~WindowsThread();

					virtual jlong getId() const;

					virtual void setPriority(Priority priority);

					virtual void start();

					virtual void join();
					virtual jbool join(jlong milliseconds);

					virtual jbool isRunning();
				};

			}
		}
	}
}

#endif
