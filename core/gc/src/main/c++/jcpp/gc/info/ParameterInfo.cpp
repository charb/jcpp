#include "jcpp/gc/info/ParameterInfo.h"
#include "jcpp/gc/info/MethodCallInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			ParameterInfo::ParameterInfo(MethodCallInfo* methodCallInfo, const char* name, void** pointer) : PointerInfo(pointer), name(name) {
				methodCallInfo->addParameterInfo(this);
			}

			ParameterInfo::~ParameterInfo() {
			}

		}
	}
}
