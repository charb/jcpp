#ifndef JCPP_NATIVE_API_IO_NATIVEFILEOUTPUTSTREAM
#define JCPP_NATIVE_API_IO_NATIVEFILEOUTPUTSTREAM

#include "jcpp/native/api/io/NativeOutputStream.h"
#include "jcpp/native/api/io/NativeFileDescriptor.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace io {

				class JCPP_EXPORT NativeFileOutputStream: public NativeOutputStream {

				private:
					NativeFileOutputStream(const NativeFileOutputStream&);
					NativeFileOutputStream& operator =(const NativeFileOutputStream&);

				protected:
					NativeFileOutputStream();

				public:
					virtual ~NativeFileOutputStream();

					virtual NativeFileDescriptor * getNativeFileDescriptor() = 0;

					virtual void write(jbyte byte) = 0;
					virtual void write(jbyte * buf, jint offset, jint length) = 0;
					virtual void flush() = 0;
					virtual void close() = 0;

				};

			}
		}
	}

}

#endif
