#ifndef JCPP_GC_FINALIZABLE_H
#define JCPP_GC_FINALIZABLE_H

#include "jcpp/native/api/NativeInclude.h"

namespace jcpp {
	namespace gc {
		class JCPP_EXPORT Finalizable {
		public:
			Finalizable();

			virtual void finalize() = 0;

			virtual ~Finalizable();
		};

	}
}

#endif


