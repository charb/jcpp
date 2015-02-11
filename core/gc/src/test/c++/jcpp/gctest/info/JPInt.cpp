#include "jcpp/gctest/info/JPInt.h"
#include <stdio.h>

namespace jcpp {
	namespace gctest {
		namespace info {

			JPInt::JPInt() : __objectInfo(&__classInfo, this, 0, null) { // injected
				MethodCallInfo __methodCallInfo(&__JPIntMethodName, &__objectInfo, 0, null, 0, null);  // injected
				this->value = 0;

				printf("JPInt Object created...\n");
			}

			JPInt::JPInt(jint value) : __objectInfo(&__classInfo, this, 0, null) { // injected
				ParameterInfo* __parameterInfos[1]; // injected
				MethodCallInfo __methodCallInfo(&__JPIntMethodName, &__objectInfo, 1, __parameterInfos, 0, null);  // injected
				ParameterInfo __valueParameterInfo(&__methodCallInfo, (void**)&value, 0);  // injected

				this->value = value;

				printf("JPInt Object created...\n");
			}

			jint JPInt::getValue() {
				MethodCallInfo __methodCallInfo(&__getValueMethodName, &__objectInfo, 0, null, 0, null);  // injected
				return value;
			}

			void JPInt::setValue(jint i) {
				MethodCallInfo __methodCallInfo(&__setValueMethodName, &__objectInfo, 0, null, 0 , null);  // injected
				value = i;
			}

			void JPInt::finalize() {
				MethodCallInfo __methodCallInfo(&__finalizeMethodName, &__objectInfo, 0, null, 0, null);  // injected
				printf("JPInt finalize...\n");
			}

			JPInt::~JPInt() {
				MethodCallInfo __methodCallInfo(&__destructorJPIntMethodName, &__objectInfo, 0, null, 0, null);  // injected
				printf("JPInt destructor...\n");
			}

			NativeString JPInt::__JPIntMethodName("JPInt");
			NativeString JPInt::__getValueMethodName("getValue");
			NativeString JPInt::__setValueMethodName("setValue");
			NativeString JPInt::__finalizeMethodName("finalize");
			NativeString JPInt::__destructorJPIntMethodName("~JPInt");

			ClassInfo JPInt::__classInfo("jcpp::gc::info", "JPInt", 0); // injected

		}
	}
}
