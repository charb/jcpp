#ifndef JCPP_NATIVE_API_THREAD_NATIVETHREADFACTORY
#define JCPP_NATIVE_API_THREAD_NATIVETHREADFACTORY

#include "jcpp/native/api/nthread/NativeCondition.h"
#include "jcpp/native/api/nthread/NativeMutex.h"
#include "jcpp/native/api/nthread/NativeThread.h"
#include <vector>

namespace jcpp {
	namespace native {
		namespace api {
			class NativeFactory;
		}
	}
}

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				class NativeThreadLocalStorage;

				class JCPP_EXPORT NativeThreadFactory {

					friend class jcpp::native::api::NativeFactory;
					friend class NativeThreadLocalStorage;
					friend class NativeThread;

				private:
					static NativeThreadFactory * instance;

				protected:
					NativeMutex * mutex;
					std::vector<NativeThread *> threads;

					NativeThreadFactory();

					static NativeThreadFactory * getInstance();
					static void setInstance(NativeThreadFactory * instance);

					void removeThread(NativeThread * thread);

				public:
					virtual ~NativeThreadFactory();

					virtual NativeMutex * createNativeMutex() = 0;
					virtual NativeCondition * createNativeCondition(NativeMutex * mutex) = 0;
					virtual NativeThread * createNativeThread(NativeRunnable * runnable) = 0;

					virtual NativeThread * mainThread() = 0;
					virtual NativeThread * currentThread() = 0;

					void getAllThreads(std::vector<NativeThread *>& threads);

				};

			}
		}
	}
}

#endif
