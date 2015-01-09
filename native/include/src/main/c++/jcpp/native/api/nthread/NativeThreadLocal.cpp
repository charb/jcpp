#include "jcpp/native/api/nthread/NativeThreadLocal.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				NativeThreadLocal::NativeThreadLocal() {

				}

				NativeThreadLocal::~NativeThreadLocal() {

				}

				void* * NativeThreadLocal::operator ->() {
					return &get();
				}

				void* & NativeThreadLocal::operator *() {
					return get();
				}

				void*& NativeThreadLocal::get() {
					NativeThreadLocalStorageSlot*& slot = NativeThreadLocalStorage::current()->get(this);
					if (!slot) {
						slot = new NativeThreadLocalStorageSlot();
					}
					return static_cast<NativeThreadLocalStorageSlot*>(slot)->getValue();
				}

			}
		}
	}

}
