#ifndef JCPP_NATIVE_UNIXOS_IO_UNIXFILEDESCRIPTOR
#define JCPP_NATIVE_UNIXOS_IO_UNIXFILEDESCRIPTOR

#include "jcpp/native/api/io/NativeFileDescriptor.h"

using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				class JCPP_EXPORT UnixFileDescriptor: public NativeFileDescriptor {

				private:
					int descriptor;

				public:
					UnixFileDescriptor();
					UnixFileDescriptor(int descriptor);
					virtual ~UnixFileDescriptor();

					void setDescriptor(int handle);
					int getDescriptor();

				};

			}
		}
	}
}

#endif
