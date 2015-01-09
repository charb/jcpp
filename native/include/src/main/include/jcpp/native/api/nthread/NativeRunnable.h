#ifndef JCPP_NATIVE_API_THREAD_NATIVERUNNABLE
#define JCPP_NATIVE_API_THREAD_NATIVERUNNABLE

#include "jcpp/native/api/NativeInclude.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

			class JCPP_EXPORT NativeRunnable {

			public:
				NativeRunnable();
				virtual ~NativeRunnable();

				virtual void run() = 0;

			};

		}
	}
}

}

#endif
