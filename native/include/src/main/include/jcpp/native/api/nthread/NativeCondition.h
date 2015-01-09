#ifndef JCPP_NATIVE_API_THREAD_NATIVECONDITION
#define JCPP_NATIVE_API_THREAD_NATIVECONDITION

#include "jcpp/native/api/nthread/NativeMutex.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				class JCPP_EXPORT NativeCondition {

				private:
					NativeCondition(const NativeCondition&);
					NativeCondition& operator =(const NativeCondition&);

				protected:
					NativeCondition();

				public:
					virtual ~NativeCondition();

					virtual NativeMutex * getMutex() = 0;

					virtual jbool wait(jlong timeout = 0) = 0;
					virtual jbool notify() = 0;
					virtual jbool notifyAll() = 0;

				};

			}
		}
	}

}

#endif
