#ifndef JCPP_GC_INFO_JPRIMITIVEINT_H
#define JCPP_GC_INFO_JPRIMITIVEINT_H

#include "jcpp/gc/info/GcInfoInclude.h"
#include "jcpp/gc/Finalizable.h"

using namespace jcpp::gc;

namespace jcpp {
	namespace gctest {
		namespace info {

			class JCPP_EXPORT JPInt : public Finalizable {

			protected:
				static ClassInfo __classInfo; // injected

				jint value;

				ObjectInfo __objectInfo; // injected
			public:
				JPInt();

				JPInt(jint value);

				jint getValue();

				void setValue(jint i);

				virtual void finalize();

				virtual ~JPInt();

			};
		}
	}
}

#endif
