#ifndef JCPP_NATIVE_API_IO_NATIVEINPUTSTREAM
#define JCPP_NATIVE_API_IO_NATIVEINPUTSTREAM

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/native/api/io/NativeFileDescriptor.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace io {


				class JCPP_EXPORT NativeInputStream {

				private:
					NativeInputStream(const NativeInputStream&);
					NativeInputStream& operator =(const NativeInputStream&);

				protected:
					NativeInputStream();

				public:
					virtual ~NativeInputStream();

					virtual jbyte read() = 0;
					virtual jint read(jbyte * buf, jint offset, jint length) = 0;
					virtual jlong skip(jlong n) = 0;
					virtual jlong available() = 0;
					virtual void close() = 0;

				};

			}
		}
	}

}

#endif
