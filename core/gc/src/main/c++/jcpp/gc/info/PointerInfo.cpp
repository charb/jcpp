#include "jcpp/gc/info/PointerInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			PointerInfo::PointerInfo(void** pointer) :
					pointer(pointer) {
			}

			void** PointerInfo::getPointer() {
				return pointer;
			}

			jlong PointerInfo::getPointedToAddress() {
				return (jlong)(*(pointer));
			}

			void PointerInfo::setPointedToAddress(jlong address) {
				*pointer = (void*)address;
			}

			PointerInfo::~PointerInfo() {
			}

		}
	}
}
