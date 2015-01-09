#include "jcpp/gctest/info/ChildSampleInfo.h"
#include <stdio.h>

namespace jcpp {
	namespace gctest {
		namespace info {

			ClassInfo ChildSampleInfo::__classInfo("jcpp::gc::info", "ChildSampleInfo"); // injected


			ChildSampleInfo::ChildSampleInfo() : SampleInfo(), childPint(null), __objectInfo(&__classInfo, this), __childPintFieldInfo("childPint", (void**)&childPint)  { // injected
				__objectInfo.addFieldInfo(&__childPintFieldInfo);  // injected

				MethodCallInfo __methodCallInfo("SampleInfo", &__objectInfo);  // injected

				printf("ChildSampleInfo Object created...\n");
			}

			JPInt* ChildSampleInfo::getChildPint() {
				MethodCallInfo __methodCallInfo("getChildPint", &__objectInfo);  // injected
				return childPint;
			}

			void ChildSampleInfo::setChildPint(JPInt* p) {
				MethodCallInfo __methodCallInfo("setChildPint", &__objectInfo);  // injected
				ParameterInfo __pParameterInfo(&__methodCallInfo, "p",  (void**)&p);  // injected

				childPint = p;
			}

			ChildSampleInfo::~ChildSampleInfo() {
				printf("ChildSampleInfo destructor...\n");
			}

		}
	}
}
