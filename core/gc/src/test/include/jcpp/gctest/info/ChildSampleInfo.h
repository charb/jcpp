#ifndef JCPP_GC_INFO_CHILDSAMPLEINFO_H
#define JCPP_GC_INFO_CHILDSAMPLEINFO_H

#include "jcpp/gc/info/GcInfoInclude.h" // injected
#include "jcpp/gctest/info/SampleInfo.h"

using namespace jcpp::gc;

namespace jcpp {
	namespace gctest {
		namespace info {

			class JCPP_EXPORT ChildSampleInfo : public SampleInfo {

			private:
				static ClassInfo __classInfo; // injected

				JPInt* childPint;
				FieldInfo __childPintFieldInfo;  // injected

				ObjectInfo __objectInfo; // injected

			public:
				ChildSampleInfo();

				JPInt* getChildPint();

				void setChildPint(JPInt* p);

				virtual ~ChildSampleInfo();

			};

		}
	}
}

#endif
