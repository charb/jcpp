#ifndef JCPP_NATIVE_WINDOWS_IO_WINDOWSFILEINPUTSTREAM
#define JCPP_NATIVE_WINDOWS_IO_WINDOWSFILEINPUTSTREAM

#include "jcpp/native/api/io/NativeFileInputStream.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/windows/io/WindowsFileDescriptor.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				class JCPP_EXPORT WindowsFileInputStream: public NativeFileInputStream {

				private:
					static NativeString className;

					WindowsFileDescriptor fileDescriptor;

					WindowsFileInputStream(const WindowsFileInputStream&);
					WindowsFileInputStream& operator =(const WindowsFileInputStream&);

				public:
					WindowsFileInputStream(const NativeString& path);
					WindowsFileInputStream(const WindowsFileDescriptor& fileDescriptor);
					virtual ~WindowsFileInputStream();

					virtual NativeFileDescriptor * getNativeFileDescriptor();

					virtual jbyte read();
					virtual jint read(jbyte * buf, jint offset, jint length);
					virtual jlong skip(jlong offset);
					virtual jlong available();
					virtual void close();

				};

			}
		}
	}

}

#endif

