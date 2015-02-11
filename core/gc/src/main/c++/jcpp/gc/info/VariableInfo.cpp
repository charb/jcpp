#include "jcpp/gc/info/VariableInfo.h"
#include "jcpp/gc/info/MethodCallInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			VariableInfo::VariableInfo(MethodCallInfo* methodCallInfo, void** pointer, jint index) : PointerInfo(pointer), methodCallInfo(methodCallInfo), index(index) {
				methodCallInfo->addVariableInfo(index, this);
			}

			VariableInfo::~VariableInfo() {
				methodCallInfo->removeVariableInfo(index);
			}

		}
	}
}
