#include "jcpp/gctest/info/SampleThreadInfo.h"
#include <stdio.h>
#include "jcpp/gc/GarbageCollector.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/gctest/info/SampleInfo.h"
#include "jcpp/gctest/info/ChildSampleInfo.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gctest {
		namespace info {

			SampleThreadInfo::SampleThreadInfo() : __objectInfo(&__classInfo, this, 0, null) { // injected
				MethodCallInfo __methodCallInfo(&__SampleThreadInfoMethodName, &__objectInfo, 0, null, 0, null);  // injected

				printf("SampleThreadInfo Object created...\n");
			}

			void SampleThreadInfo::run() {
				VariableInfo* __variableInfos[5]; // injected
				MethodCallInfo __methodCallInfo(&__runMethodName, &__objectInfo, 0, null, 5, __variableInfos);  // injected

				printf("SampleInfo GC Test ...\n");

				{
					JPInt* pi = new JPInt();
					VariableInfo __piVariableInfo(&__methodCallInfo, (void**)&pi, 0);  // injected

					SampleInfo* sampleInfo = new SampleInfo(pi);
					VariableInfo __sampleInfoVariableInfo(&__methodCallInfo, (void**)&sampleInfo, 1);  // injected
				}

				printf(">>> Calling gc ...\n");
				GarbageCollector::getGarbageCollector()->gc();
				GarbageCollector::getGarbageCollector()->gc();

				NativeFactory::getNativeThreadFactory()->currentThread()->sleep(1000);

				printf("ChildSampleInfo GC Test ...\n");

				{

					ChildSampleInfo* childSampleInfo = new ChildSampleInfo();
					VariableInfo __childSampleInfoVariableInfo(&__methodCallInfo, (void**)&childSampleInfo, 2);  // injected

					{
						JPInt* pi = new JPInt();
						VariableInfo __piVariableInfo(&__methodCallInfo, (void**)&pi, 3);  // injected
						childSampleInfo->setPint(pi);

						JPInt* cpi = new JPInt();
						VariableInfo __cpiVariableInfo(&__methodCallInfo, (void**)&cpi, 4);  // injected
						childSampleInfo->setChildPint(cpi);
					}

					printf(">>> Calling gc ...\n");
					GarbageCollector::getGarbageCollector()->gc();
					GarbageCollector::getGarbageCollector()->gc();

					NativeFactory::getNativeThreadFactory()->currentThread()->sleep(1000);
				}

				printf(">>> Calling gc ...\n");
				GarbageCollector::getGarbageCollector()->gc();
				GarbageCollector::getGarbageCollector()->gc();

				NativeFactory::getNativeThreadFactory()->currentThread()->sleep(1000);
			}

			void SampleThreadInfo::finalize() {
				MethodCallInfo __methodCallInfo(&__finalizeMethodName, &__objectInfo, 0, null, 0, null);  // injected
				printf("SampleThreadInfo finalize...\n");
			}

			SampleThreadInfo::~SampleThreadInfo() {
				MethodCallInfo __methodCallInfo(&__destructorSampleThreadInfoMethodName, &__objectInfo, 0, null, 0, null);  // injected
				printf("SampleThreadInfo destructor...\n");
			}

			NativeString SampleThreadInfo::__SampleThreadInfoMethodName("SampleThreadInfo"); // injected
			NativeString SampleThreadInfo::__runMethodName("run"); // injected
			NativeString SampleThreadInfo::__finalizeMethodName("finalize"); // injected
			NativeString SampleThreadInfo::__destructorSampleThreadInfoMethodName("~SampleThreadInfo"); // injected

			ClassInfo SampleThreadInfo::__classInfo("jcpp::gc::info", "SampleThreadInfo", 0); // injected
		}
	}
}
