#ifndef JCPP_NATIVE_API_IO_NATIVEOUTPUTSTREAM
#define JCPP_NATIVE_API_IO_NATIVEOUTPUTSTREAM

#include "jcpp/native/api/NativeInclude.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace io {


				class JCPP_EXPORT NativeOutputStream {

				private:
					NativeOutputStream(const NativeOutputStream&);
					NativeOutputStream& operator =(const NativeOutputStream&);

				protected:
					NativeOutputStream();

				public:
					virtual ~NativeOutputStream();

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
