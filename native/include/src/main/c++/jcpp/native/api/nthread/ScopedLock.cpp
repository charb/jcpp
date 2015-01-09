#include "jcpp/native/api/nthread/ScopedLock.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				ScopedLock::ScopedLock(NativeMutex& mutex) :
						nativeMutex(mutex) {
					nativeMutex.lock();
				}

				ScopedLock::~ScopedLock() {
					nativeMutex.unlock();
				}

			}
		}
	}
}
