#ifndef JCPP_NATIVE_WINDOWS_IO_WINDOWSFILEDESCRIPTOR
#define JCPP_NATIVE_WINDOWS_IO_WINDOWSFILEDESCRIPTOR

#include "jcpp/native/api/io/NativeFileDescriptor.h"

#include "jcpp/native/windows/WindowsInclude.h"

using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				class JCPP_EXPORT WindowsFileDescriptor: public NativeFileDescriptor {

				private:
					HANDLE handle;

				public:
					WindowsFileDescriptor();
					WindowsFileDescriptor(HANDLE handle);
					virtual ~WindowsFileDescriptor();

					void setHandle(HANDLE handle);
					HANDLE getHandle();

				};

			}
		}
	}
}

#endif
