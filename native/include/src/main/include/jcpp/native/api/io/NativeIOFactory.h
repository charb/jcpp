#ifndef JCPP_NATIVE_API_IO_NATIVEIOFACTORY
#define JCPP_NATIVE_API_IO_NATIVEIOFACTORY

#include "jcpp/native/api/io/NativeFileInputStream.h"
#include "jcpp/native/api/io/NativeFileOutputStream.h"
#include "jcpp/native/api/NativeString.h"

namespace jcpp {
	namespace native {
		namespace api {
			class NativeFactory;
		}
	}
}

namespace jcpp {
	namespace native {
		namespace api {
			namespace io {

				class JCPP_EXPORT NativeIOFactory {

					friend class jcpp::native::api::NativeFactory;

				private:
					static NativeIOFactory * instance;

				protected:
					NativeIOFactory();

					static NativeIOFactory * getInstance();
					static void setInstance(NativeIOFactory * instance);

				public:
					virtual ~NativeIOFactory();

					virtual NativeInputStream * getStandardInputStream() = 0;
					virtual NativeOutputStream * getStandardOutputStream() = 0;
					virtual NativeOutputStream * getStandardErrorStream() = 0;

					virtual NativeFileInputStream * createFileInputStream(const NativeString& path) = 0;
					virtual NativeFileOutputStream * createFileOutputStream(const NativeString& path, jbool append = false) = 0;

				};

			}
		}
	}
}

#endif
