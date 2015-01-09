#ifndef JCPP_NATIVE_WINDOWS_THREAD_WINDOWSMAINTHREAD
#define JCPP_NATIVE_WINDOWS_THREAD_WINDOWSMAINTHREAD

#include "jcpp/native/windows/nthread/WindowsAbstractThread.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				class JCPP_EXPORT WindowsMainThread: public WindowsAbstractThread {

				private:
					static NativeString className;
					static WindowsMainThread instance;

					int priorityToNativePriority();

					WindowsMainThread();
				public:
					static WindowsMainThread * getInstance();

					virtual ~WindowsMainThread();

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
