#ifndef JCPP_NATIVE_WINDOWS_IO_WINDOWSFILEOUTPUTSTREAM
#define JCPP_NATIVE_WINDOWS_IO_WINDOWSFILEOUTPUTSTREAM

#include "jcpp/native/api/io/NativeFileOutputStream.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/windows/io/WindowsFileDescriptor.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				class JCPP_EXPORT WindowsFileOutputStream: public NativeFileOutputStream {

				private:
					static NativeString className;

					WindowsFileDescriptor fileDescriptor;

					WindowsFileOutputStream(const WindowsFileOutputStream&);
					WindowsFileOutputStream& operator =(const WindowsFileOutputStream&);

				public:
					WindowsFileOutputStream(const NativeString& path, jbool append);
					WindowsFileOutputStream(const WindowsFileDescriptor& fileDescriptor);
					virtual ~WindowsFileOutputStream();

					virtual NativeFileDescriptor * getNativeFileDescriptor();

					virtual void write(jbyte byte);
					virtual void write(jbyte * buf, jint offset, jint length);
					virtual void flush();
					virtual void close();

				};

			}
		}
	}

}

#endif
