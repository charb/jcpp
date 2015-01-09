#ifndef JCPP_NATIVE_API_IO_NATIVEFILEDESCRIPTOR
#define JCPP_NATIVE_API_IO_NATIVEFILEDESCRIPTOR

#include "jcpp/native/api/NativeInclude.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace io {

				class JCPP_EXPORT NativeFileDescriptor {

				protected:
					NativeFileDescriptor();

				public:
					virtual ~NativeFileDescriptor();

				};

			}
		}
	}
}

#endif
