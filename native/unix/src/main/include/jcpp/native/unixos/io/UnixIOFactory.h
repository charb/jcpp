#ifndef JCPP_NATIVE_UNIXOS_IO_UNIXIOFACTORY
#define JCPP_NATIVE_UNIXOS_IO_UNIXIOFACTORY

#include "jcpp/native/api/io/NativeIOFactory.h"
#include "jcpp/native/unixos/io/UnixStandardInputStream.h"
#include "jcpp/native/unixos/io/UnixStandardOutputStream.h"

using namespace jcpp::native::api::io;
using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				class JCPP_EXPORT UnixIOFactory: public NativeIOFactory {

				private:

					UnixStandardInputStream standardInputStream;
					UnixStandardOutputStream standardOutputStream;
					UnixStandardOutputStream standardErrorStream;

				public:
					UnixIOFactory();
					virtual ~UnixIOFactory();

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
