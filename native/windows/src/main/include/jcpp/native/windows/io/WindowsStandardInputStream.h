#ifndef JCPP_NATIVE_WINDOWS_IO_WINDOWSSTANDARDINPUTSTREAM
#define JCPP_NATIVE_WINDOWS_IO_WINDOWSSTANDARDINPUTSTREAM

#include "jcpp/native/api/io/NativeInputStream.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/windows/WindowsInclude.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				class JCPP_EXPORT WindowsStandardInputStream: public NativeInputStream {

				private:
					static NativeString className;

					HANDLE stdHandle;

					WindowsStandardInputStream(const WindowsStandardInputStream&);
					WindowsStandardInputStream& operator =(const WindowsStandardInputStream&);

				public:
					WindowsStandardInputStream();
					virtual ~WindowsStandardInputStream();

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

