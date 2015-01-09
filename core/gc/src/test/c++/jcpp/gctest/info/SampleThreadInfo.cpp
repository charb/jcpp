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

			ClassInfo SampleThreadInfo::__classInfo("jcpp::gc::info", "SampleThreadInfo"); // injected


			SampleThreadInfo::SampleThreadInfo() : __objectInfo(&__classInfo, this) { // injected
				MethodCallInfo __methodCallInfo("SampleThreadInfo", &__objectInfo);  // injected

				printf("SampleThreadInfo Object created...\n");
			}

			void SampleThreadInfo::run() {
				MethodCallInfo __methodCallInfo("run", &__objectInfo);  // injected

				printf("SampleInfo GC Test ...\n");

				{
					JPInt* pi = new JPInt();
					VariableInfo __piVariableInfo(&__methodCallInfo, (void**)&pi);  // injected

					SampleInfo* sampleInfo = new SampleInfo(pi);
					VariableInfo __sampleInfoVariableInfo(&__methodCallInfo, (void**)&sampleInfo);  // injected
				}

				printf(">>> Calling gc ...\n");
				GarbageCollector::getGarbageCollector()->gc();
				GarbageCollector::getGarbageCollector()->gc();

				NativeFactory::getNativeThreadFactory()->currentThread()->sleep(1000);

				printf("ChildSampleInfo GC Test ...\n");

				{

					ChildSampleInfo* childSampleInfo = new ChildSampleInfo();
					VariableInfo __childSampleInfoVariableInfo(&__methodCallInfo, (void**)&childSampleInfo);  // injected

					{
						JPInt* pi = new JPInt();
						VariableInfo __piVariableInfo(&__methodCallInfo, (void**)&pi);  // injected
						childSampleInfo->setPint(pi);

						JPInt* cpi = new JPInt();
						VariableInfo __cpiVariableInfo(&__methodCallInfo, (void**)&cpi);  // injected
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
				printf("SampleThreadInfo finalize...\n");
			}

			SampleThreadInfo::~SampleThreadInfo() {
				printf("SampleThreadInfo destructor...\n");
			}
		}
	}
}
