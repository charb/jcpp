#ifndef JCPP_GC_INFO_SAMPLEINFO_H
#define JCPP_GC_INFO_SAMPLEINFO_H

#include "jcpp/gc/info/GcInfoInclude.h" // injected
#include "jcpp/gctest/info/JPInt.h"
#include "jcpp/gc/Finalizable.h"

using namespace jcpp::gc;

namespace jcpp {
	namespace gctest {
		namespace info {

			class JCPP_EXPORT SampleInfo : public Finalizable {

			private:

				static NativeString __SampleInfoMethodName; // injected
				static NativeString __staticInfoMethodName; // injected
				static NativeString __getPintMethodName; // injected
				static NativeString __setPintMethodName; // injected
				static NativeString __getNextMethodName; // injected
				static NativeString __setNextMethodName; // injected
				static NativeString __processMethodName; // injected
				static NativeString __finalizeMethodName; // injected
				static NativeString __destructorSampleInfoMethodName; // injected

				static ClassInfo __classInfo; // injected

				static JPInt* counter;
				static FieldInfo __counterStaticFieldInfo;  // injected

				JPInt* pint;
				static NativeString __pintFieldName;  // injected
				FieldInfo __pintFieldInfo;  // injected

				SampleInfo* next;
				static NativeString __nextFieldName;  // injected
				FieldInfo __nextFieldInfo; // injected

				FieldInfo* __fieldInfos[2]; // injected
				ObjectInfo __objectInfo; // injected

			public:
				SampleInfo();

				SampleInfo(JPInt* p);

				static void staticInfo();

				JPInt* getPint();

				void setPint(JPInt* p);

				SampleInfo* getNext();

				void setNext(SampleInfo* p);

				JPInt* process(JPInt* pi1, JPInt* pi2);

				virtual void finalize();

				virtual ~SampleInfo();

			};

		}
	}
}

#endif
