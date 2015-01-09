#include "jcpp/gctest/info/SampleInfo.h"
#include <stdio.h>

namespace jcpp {
	namespace gctest {
		namespace info {

			ClassInfo SampleInfo::__classInfo("jcpp::gc::info", "SampleInfo"); // injected

			JPInt* SampleInfo::counter = new JPInt(1);

			FieldInfo SampleInfo::__counterStaticFieldInfo(&__classInfo, "counter", (void**)&counter);  // injected

			SampleInfo::SampleInfo() : pint(null), next(null), __objectInfo(&__classInfo, this), __pintFieldInfo("pint", (void**)&pint) , __nextFieldInfo("next", (void**)&next) { // injected
				__objectInfo.addFieldInfo(&__pintFieldInfo);  // injected
				__objectInfo.addFieldInfo(&__nextFieldInfo);  // injected

				MethodCallInfo __methodCallInfo("SampleInfo", &__objectInfo);  // injected

				printf("SampleInfo Object created...\n");
			}

			SampleInfo::SampleInfo(JPInt* p) : pint(p), next(null), __objectInfo(&__classInfo, this), __pintFieldInfo("pint", (void**)&pint) , __nextFieldInfo("next", (void**)&next) { // injected
				__objectInfo.addFieldInfo(&__pintFieldInfo); // injected

				MethodCallInfo __methodCallInfo("SampleInfo", &__objectInfo);  // injected
				ParameterInfo __pParameterInfo(&__methodCallInfo, "p", (void**)&p);  // injected

				JPInt* temp = null;
				VariableInfo __tempVariableInfo(&__methodCallInfo, (void**)&temp);  // injected

				printf("SampleInfo Object created...\n");
			}

			void SampleInfo::staticInfo() {
				MethodCallInfo __methodCallInfo("staticInfo", null);  // injected
			}

			JPInt* SampleInfo::getPint() {
				MethodCallInfo __methodCallInfo("getPint", &__objectInfo);  // injected

				return pint;
			}

			void SampleInfo::setPint(JPInt* p) {
				MethodCallInfo __methodCallInfo("setPint", &__objectInfo);  // injected
				ParameterInfo __pParameterInfo(&__methodCallInfo, "p",  (void**)&p);  // injected

				pint = p;
			}

			SampleInfo* SampleInfo::getNext() {
				 MethodCallInfo __methodCallInfo("getNext", &__objectInfo);  // injected
				return next;
			}

			void SampleInfo::setNext(SampleInfo* p) {
				MethodCallInfo __methodCallInfo("setNext", &__objectInfo);  // injected
				ParameterInfo __pParameterInfo(&__methodCallInfo, "p",  (void**)&p);  // injected
				next = p;
			}

			JPInt* SampleInfo::process(JPInt* pi1, JPInt* pi2) {
				MethodCallInfo __methodCallInfo("process", &__objectInfo);  // injected
				ParameterInfo __pi1ParameterInfo(&__methodCallInfo, "pi1", (void**)&pi1);  // injected
				ParameterInfo __pi2ParameterInfo(&__methodCallInfo, "pi2", (void**)&pi2);  // injected

				JPInt* pi3 = new JPInt(pi1->getValue() + pi2->getValue());
				VariableInfo __pi3VariableInfo(&__methodCallInfo, (void**)&pi3);  // injected

				if(pi3->getValue() > 10 ) {
					JPInt* temp = null;
					VariableInfo __tempVariableInfo(&__methodCallInfo, (void**)&temp);  // injected

					if(pi3->getValue() > 20 ) {
						temp = new JPInt(pi3->getValue() - 20);
					} else {
						temp = new JPInt(pi3->getValue() - 10);
					}

					return temp;
				}

				return pi3;
			}

			void SampleInfo::finalize() {
				printf("SampleInfo finalize...\n");
			}

			SampleInfo::~SampleInfo() {
				printf("SampleInfo destructor...\n");
			}

		}
	}
}
