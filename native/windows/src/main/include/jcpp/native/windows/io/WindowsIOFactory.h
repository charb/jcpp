#ifndef JCPP_NATIVE_WINDOWS_IO_WINDOWSIOFACTORY
#define JCPP_NATIVE_WINDOWS_IO_WINDOWSIOFACTORY

#include "jcpp/native/api/io/NativeIOFactory.h"
#include "jcpp/native/windows/io/WindowsStandardInputStream.h"
#include "jcpp/native/windows/io/WindowsStandardOutputStream.h"

using namespace jcpp::native::api::io;
using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				class JCPP_EXPORT WindowsIOFactory: public NativeIOFactory {

				private:

					WindowsStandardInputStream standardInputStream;
					WindowsStandardOutputStream standardOutputStream;
					WindowsStandardOutputStream standardErrorStream;

				public:
					WindowsIOFactory();
					virtual ~WindowsIOFactory();

					virtual NativeInputStream * getStandardInputStream();
					virtual NativeOutputStream * getStandardOutputStream();
					virtual NativeOutputStream * getStandardErrorStream();

					virtual NativeFileInputStream * createFileInputStream(const NativeString& path);
					virtual NativeFileOutputStream * createFileOutputStream(const NativeString& path, jbool append = false);

				};

			}
		}
	}
}

#endif
