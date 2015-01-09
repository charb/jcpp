#ifndef JCPP_NATIVE_API_THREAD_NATIVETHREADLOCAL
#define JCPP_NATIVE_API_THREAD_NATIVETHREADLOCAL

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/native/api/nthread/NativeThreadLocal.h"
#include "jcpp/native/api/nthread/NativeThreadLocalStorage.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				class JCPP_EXPORT NativeThreadLocal {

				private:
					NativeThreadLocal(const NativeThreadLocal&);
					NativeThreadLocal& operator =(const NativeThreadLocal&);

				public:

					NativeThreadLocal();
					~NativeThreadLocal();

					void* * operator ->();
					void* & operator *();

					void*& get();

				};

			}
		}
	}

}

#endif
