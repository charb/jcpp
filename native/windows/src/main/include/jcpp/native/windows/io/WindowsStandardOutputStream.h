#ifndef JCPP_NATIVE_WINDOWS_IO_WINDOWSSTANDARDOUTPUTSTREAM
#define JCPP_NATIVE_WINDOWS_IO_WINDOWSSTANDARDOUTPUTSTREAM

#include "jcpp/native/api/io/NativeOutputStream.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/windows/WindowsInclude.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				class JCPP_EXPORT WindowsStandardOutputStream: public NativeOutputStream {

				private:
					static NativeString className;

					HANDLE stdHandle;

					WindowsStandardOutputStream(const WindowsStandardOutputStream&);
					WindowsStandardOutputStream& operator =(const WindowsStandardOutputStream&);

				public:
					WindowsStandardOutputStream(jbool out);
					virtual ~WindowsStandardOutputStream();

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
