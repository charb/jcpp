#include "jcpp/gc/info/VariableInfo.h"
#include "jcpp/gc/info/MethodCallInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			VariableInfo::VariableInfo(MethodCallInfo* methodCallInfo, void** pointer) : PointerInfo(pointer), methodCallInfo(methodCallInfo) {
				methodCallInfo->addVariableInfo(this);
			}

			VariableInfo::~VariableInfo() {
				methodCallInfo->removeVariableInfo(this);
			}

		}
	}
}
