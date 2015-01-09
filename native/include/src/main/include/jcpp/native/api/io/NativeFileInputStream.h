#ifndef JCPP_NATIVE_API_IO_NATIVEFILEINPUTSTREAM
#define JCPP_NATIVE_API_IO_NATIVEFILEINPUTSTREAM

#include "jcpp/native/api/io/NativeFileDescriptor.h"
#include "jcpp/native/api/io/NativeInputStream.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace io {

				class JCPP_EXPORT NativeFileInputStream : public NativeInputStream {

				private:
					NativeFileInputStream(const NativeFileInputStream&);
					NativeFileInputStream& operator =(const NativeFileInputStream&);

				protected:
					NativeFileInputStream();

				public:
					virtual ~NativeFileInputStream();

					virtual NativeFileDescriptor * getNativeFileDescriptor() = 0;

					virtual jbyte read() = 0;
					virtual jint read(jbyte * buf, jint offset, jint length) = 0;
					virtual jlong skip(jlong offset) = 0;
					virtual jlong available() = 0;
					virtual void close() = 0;

				};

			}
		}
	}

}

#endif
