#include "jcpp/gctest/info/JPInt.h"
#include <stdio.h>

namespace jcpp {
	namespace gctest {
		namespace info {

			ClassInfo JPInt::__classInfo("jcpp::gc::info", "JPInt"); // injected

			JPInt::JPInt() : __objectInfo(&__classInfo, this) { // injected
				MethodCallInfo __methodCallInfo("JPInt", &__objectInfo);  // injected
				this->value = 0;

				printf("JPInt Object created...\n");
			}

			JPInt::JPInt(jint value) : __objectInfo(&__classInfo, this) { // injected
				MethodCallInfo __methodCallInfo("JPInt", &__objectInfo);  // injected
				ParameterInfo __valueParameterInfo(&__methodCallInfo, "value", (void**)&value);  // injected

				this->value = value;

				printf("JPInt Object created...\n");
			}

			jint JPInt::getValue() {
				MethodCallInfo __methodCallInfo("getValue", &__objectInfo);  // injected
				return value;
			}

			void JPInt::setValue(jint i) {
				MethodCallInfo __methodCallInfo("setValue", &__objectInfo);  // injected
				value = i;
			}

			void JPInt::finalize() {
				printf("JPInt finalize...\n");
			}

			JPInt::~JPInt() {
				printf("JPInt destructor...\n");
			}

		}
	}
}
