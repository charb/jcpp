#ifndef JCPP_NATIVE_UNIXOS_THREAD_UNIXTHREADFACTORY
#define JCPP_NATIVE_UNIXOS_THREAD_UNIXTHREADFACTORY

#include "jcpp/native/api/nthread/NativeThreadFactory.h"

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				class JCPP_EXPORT UnixThreadFactory: public NativeThreadFactory {

				public:
					UnixThreadFactory();
					virtual ~UnixThreadFactory();

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
