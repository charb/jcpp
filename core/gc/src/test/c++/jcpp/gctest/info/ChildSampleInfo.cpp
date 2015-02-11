#include "jcpp/gctest/info/ChildSampleInfo.h"
#include <stdio.h>

namespace jcpp {
	namespace gctest {
		namespace info {

			ChildSampleInfo::ChildSampleInfo() : SampleInfo(), childPint(null), __objectInfo(&__classInfo, this, 1, __fieldInfos), __childPintFieldInfo(&__childPintFieldName, (void**)&childPint)  { // injected
				__objectInfo.addFieldInfo(0, &__childPintFieldInfo);  // injected

				MethodCallInfo __methodCallInfo(&__ChildSampleInfoMethodName, &__objectInfo, 0, null, 0, null);  // injected

				printf("ChildSampleInfo Object created...\n");
			}

			JPInt* ChildSampleInfo::getChildPint() {
				MethodCallInfo __methodCallInfo(&__getChildPintMethodName, &__objectInfo, 0, null, 0, null);  // injected
				return childPint;
			}

			void ChildSampleInfo::setChildPint(JPInt* p) {
				ParameterInfo* __parameterInfos[1]; // injected
				MethodCallInfo __methodCallInfo(&__setChildPintMethodName, &__objectInfo, 1, __parameterInfos, 0, null);  // injected
				ParameterInfo __pParameterInfo(&__methodCallInfo,  (void**)&p, 0);  // injected

				childPint = p;
			}

			ChildSampleInfo::~ChildSampleInfo() {
				MethodCallInfo __methodCallInfo(&__destructorChildSampleInfoMethodName, &__objectInfo, 0, null, 0, null);  // injected
				printf("ChildSampleInfo destructor...\n");
			}

			NativeString ChildSampleInfo::__ChildSampleInfoMethodName("ChildSampleInfo");
			NativeString ChildSampleInfo::__getChildPintMethodName("getChildPint");
			NativeString ChildSampleInfo::__setChildPintMethodName("setChildPint");
			NativeString ChildSampleInfo::__destructorChildSampleInfoMethodName("~ChildSampleInfo");

			ClassInfo ChildSampleInfo::__classInfo("jcpp::gc::info", "ChildSampleInfo", 0); // injected

			NativeString ChildSampleInfo::__childPintFieldName("childPint");

		}
	}
}
