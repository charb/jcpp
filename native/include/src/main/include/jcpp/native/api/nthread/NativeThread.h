#ifndef JCPP_NATIVE_API_THREAD_NATIVETHREAD
#define JCPP_NATIVE_API_THREAD_NATIVETHREAD

#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/api/nthread/NativeRunnable.h"
#include "jcpp/native/api/nthread/NativeThreadLocalStorage.h"
#include "jcpp/native/api/nthread/NativeStackTraceElement.h"
#include <vector>


namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				enum Priority {
					LOWEST=1, LOW=3, NORMAL=5, HIGH=7, HIGHEST=10
				};

				enum ThreadState {
					NTH_NEW, NTH_RUNNABLE, NTH_TERMINATED
				};

				class JCPP_EXPORT NativeThread {

				private:
					NativeThread(const NativeThread&);
					NativeThread& operator =(const NativeThread&);

				protected:

					NativeThreadLocalStorage * storage;
					NativeRunnable * runnable;
					void* attachment;
					void* gcThreadInfo;
					jbool deleteOnFinish;
					ThreadState state;

					NativeThread(NativeRunnable * runnable);

				public:
					virtual ~NativeThread();

					NativeThreadLocalStorage * getStorage();

					void setGcThreadInfo(void* threadInfo);
					void* getGcThreadInfo();

					void setAttachment(void* attachment);
					void* getAttachment();

					void setDeleteOnFinish(jbool deleteOnFinish);
					jbool isDeleteOnFinish();

					ThreadState getState();

					virtual jlong getId() const = 0;
					virtual NativeString getName() = 0;
					virtual void setName(NativeString& name) = 0;

					virtual Priority getPriority() = 0;
					virtual void setPriority(Priority priority) = 0;

					virtual void start() = 0;

					virtual void join() = 0;
					virtual jbool join(jlong milliseconds) = 0;

					virtual jbool isRunning() = 0;

					virtual void sleep(jlong milliseconds) = 0;
					virtual void yield() = 0;

					virtual void suspend() = 0;
					virtual void resume() = 0;

					virtual void getStackTrace(std::vector<NativeStackTraceElement> &stackTrace) = 0;
				};

			}
		}
	}

}

#endif
