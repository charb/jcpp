#ifndef JCPP_GC_INFO_POINTERINFO_H
#define JCPP_GC_INFO_POINTERINFO_H

#include "jcpp/native/api/NativeInclude.h"

namespace jcpp {
	namespace gc {
		namespace info {

			class JCPP_EXPORT PointerInfo {
			private:
				void** pointer;

			public:
				PointerInfo(void** pointer);

				void** getPointer();

				jlong getPointedToAddress();

				void setPointedToAddress(jlong address);

				virtual ~PointerInfo();
			};

		}
	}
}

#endif
