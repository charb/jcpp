#include "jcpp/gc/info/ParameterInfo.h"
#include "jcpp/gc/info/MethodCallInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			ParameterInfo::ParameterInfo(MethodCallInfo* methodCallInfo, void** pointer, jint index) : PointerInfo(pointer) {
				methodCallInfo->addParameterInfo(index, this);
			}

			ParameterInfo::~ParameterInfo() {
			}

		}
	}
}
