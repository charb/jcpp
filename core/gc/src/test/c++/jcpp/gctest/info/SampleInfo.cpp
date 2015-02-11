#include "jcpp/gctest/info/SampleInfo.h"
#include <stdio.h>

namespace jcpp {
	namespace gctest {
		namespace info {

			JPInt* SampleInfo::counter = new JPInt(1);

			SampleInfo::SampleInfo() : pint(null), next(null), __objectInfo(&__classInfo, this, 2, __fieldInfos), __pintFieldInfo(&__pintFieldName, (void**)&pint) , __nextFieldInfo(&__nextFieldName, (void**)&next) { // injected
				__objectInfo.addFieldInfo(0, &__pintFieldInfo);  // injected
				__objectInfo.addFieldInfo(1, &__nextFieldInfo);  // injected

				MethodCallInfo __methodCallInfo(&__SampleInfoMethodName, &__objectInfo, 0, null, 0, null);  // injected

				printf("SampleInfo Object created...\n");
			}

			SampleInfo::SampleInfo(JPInt* p) : pint(p), next(null), __objectInfo(&__classInfo, this, 2, __fieldInfos), __pintFieldInfo(&__pintFieldName, (void**)&pint) , __nextFieldInfo(&__nextFieldName, (void**)&next) { // injected
				__objectInfo.addFieldInfo(0, &__pintFieldInfo); // injected
				__objectInfo.addFieldInfo(1, &__nextFieldInfo); // injected

				ParameterInfo* __parameterInfos[1]; // injected
				VariableInfo* __variableInfos[1]; // injected
				MethodCallInfo __methodCallInfo(&__SampleInfoMethodName, &__objectInfo, 1, __parameterInfos, 1, __variableInfos);  // injected
				ParameterInfo __pParameterInfo(&__methodCallInfo, (void**)&p, 0);  // injected

				JPInt* temp = null;
				VariableInfo __tempVariableInfo(&__methodCallInfo, (void**)&temp, 0);  // injected

				printf("SampleInfo Object created...\n");
			}

			void SampleInfo::staticInfo() {
				MethodCallInfo __methodCallInfo(&__staticInfoMethodName, null, 0, null, 0, null);  // injected
			}

			JPInt* SampleInfo::getPint() {
				MethodCallInfo __methodCallInfo(&__getPintMethodName, &__objectInfo, 0, null, 0, null);  // injected

				return pint;
			}

			void SampleInfo::setPint(JPInt* p) {
				ParameterInfo* __parameterInfos[1]; // injected
				MethodCallInfo __methodCallInfo(&__setPintMethodName, &__objectInfo, 1, __parameterInfos, 0, null);  // injected
				ParameterInfo __pParameterInfo(&__methodCallInfo, (void**)&p, 0);  // injected

				pint = p;
			}

			SampleInfo* SampleInfo::getNext() {
				 MethodCallInfo __methodCallInfo(&__getNextMethodName, &__objectInfo, 0, null, 0, null);  // injected
				return next;
			}

			void SampleInfo::setNext(SampleInfo* p) {
				ParameterInfo* __parameterInfos[1]; // injected
				MethodCallInfo __methodCallInfo(&__setNextMethodName, &__objectInfo, 1, __parameterInfos, 0, null);  // injected
				ParameterInfo __pParameterInfo(&__methodCallInfo,  (void**)&p, 0);  // injected
				next = p;
			}

			JPInt* SampleInfo::process(JPInt* pi1, JPInt* pi2) {
				ParameterInfo* __parameterInfos[2]; // injected
				VariableInfo* __variableInfos[2]; // injected
				MethodCallInfo __methodCallInfo(&__processMethodName, &__objectInfo, 2, __parameterInfos, 2, __variableInfos);  // injected
				ParameterInfo __pi1ParameterInfo(&__methodCallInfo, (void**)&pi1, 0); // injected
				ParameterInfo __pi2ParameterInfo(&__methodCallInfo, (void**)&pi2, 1); // injected

				JPInt* pi3 = new JPInt(pi1->getValue() + pi2->getValue());
				VariableInfo __pi3VariableInfo(&__methodCallInfo, (void**)&pi3, 0);  // injected

				if(pi3->getValue() > 10 ) {
					JPInt* temp = null;
					VariableInfo __tempVariableInfo(&__methodCallInfo, (void**)&temp, 1);  // injected

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
				MethodCallInfo __methodCallInfo(&__finalizeMethodName, &__objectInfo, 0, null, 0, null);  // injected
				printf("SampleInfo finalize...\n");
			}

			SampleInfo::~SampleInfo() {
				MethodCallInfo __methodCallInfo(&__destructorSampleInfoMethodName, &__objectInfo, 0, null, 0, null);  // injected
				printf("SampleInfo destructor...\n");
			}

			NativeString SampleInfo::__SampleInfoMethodName("SampleInfo"); // injected
			NativeString SampleInfo::__staticInfoMethodName("staticInfo"); // injected
			NativeString SampleInfo::__getPintMethodName("getPint"); // injected
			NativeString SampleInfo::__setPintMethodName("setPint"); // injected
			NativeString SampleInfo::__getNextMethodName("getNext"); // injected
			NativeString SampleInfo::__setNextMethodName("setNext"); // injected
			NativeString SampleInfo::__processMethodName("process"); // injected
			NativeString SampleInfo::__finalizeMethodName("finalize"); // injected
			NativeString SampleInfo::__destructorSampleInfoMethodName("~SampleInfo"); // injected

			ClassInfo SampleInfo::__classInfo("jcpp::gc::info", "SampleInfo", 1); // injected

			FieldInfo SampleInfo::__counterStaticFieldInfo(&__classInfo, new NativeString("counter"), (void**)&counter, 0);  // injected

			NativeString SampleInfo::__pintFieldName("pint"); // injected
			NativeString SampleInfo::__nextFieldName("next"); // injected


		}
	}
}
