#ifndef JCPP_GC_INFO_SAMPLETHREADINFO_H
#define JCPP_GC_INFO_SAMPLETHREADINFO_H

#include "jcpp/gc/info/GcInfoInclude.h"
#include "jcpp/gc/Finalizable.h"

using namespace jcpp::gc;

namespace jcpp {
	namespace gctest {
		namespace info {

			class JCPP_EXPORT SampleThreadInfo : public Finalizable {

			private:
				static ClassInfo __classInfo; // injected

				ObjectInfo __objectInfo; // injected
			public:
				SampleThreadInfo();

				void run();

				virtual void finalize();

				virtual ~SampleThreadInfo();
			};

		}
	}
}

#endif
