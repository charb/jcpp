#ifndef JCPP_NATIVE_WINDOWS_THREAD_WINDOWSTHREADFACTORY
#define JCPP_NATIVE_WINDOWS_THREAD_WINDOWSTHREADFACTORY

#include "jcpp/native/api/nthread/NativeThreadFactory.h"

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				class JCPP_EXPORT WindowsThreadFactory: public NativeThreadFactory {

				public:
					WindowsThreadFactory();
					virtual ~WindowsThreadFactory();

					virtual NativeMutex * createNativeMutex();
					virtual NativeCondition * createNativeCondition(NativeMutex * mutex);
					virtual NativeThread * createNativeThread(NativeRunnable * runnable);

					virtual NativeThread * mainThread();
					virtual NativeThread * currentThread();

				};

			}
		}
	}
}

#endif
