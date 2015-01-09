#ifndef JCPP_NATIVE_API_THREAD_SCOPEDLOCK
#define JCPP_NATIVE_API_THREAD_SCOPEDLOCK

#include "jcpp/native/api/nthread/NativeMutex.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				class JCPP_EXPORT ScopedLock {

				private:
					NativeMutex& nativeMutex;

					ScopedLock();
					ScopedLock(const ScopedLock&);
					ScopedLock& operator =(const ScopedLock&);

				public:

					ScopedLock(NativeMutex& mutex);
					~ScopedLock();

				};

			}
		}
	}

}

#endif
