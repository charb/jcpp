#include "jcpp/native/api/nthread/NativeMutex.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				NativeMutex::NativeMutex() :
						listener(null) {
				}

				NativeMutex::~NativeMutex() {
				}

				NativeMutexListener * NativeMutex::getListener() {
					return listener;
				}

				void NativeMutex::setListener(NativeMutexListener * newListener) {
					listener = newListener;
				}

				NativeMutexListener::NativeMutexListener() {
				}

				NativeMutexListener::~NativeMutexListener() {
				}

			}
		}
	}

}
