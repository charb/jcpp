#ifndef JCPP_NATIVE_UNIXOS_IO_UNIXSTANDARDINPUTSTREAM
#define JCPP_NATIVE_UNIXOS_IO_UNIXSTANDARDINPUTSTREAM

#include "jcpp/native/api/io/NativeInputStream.h"
#include "jcpp/native/api/NativeString.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				class JCPP_EXPORT UnixStandardInputStream: public NativeInputStream {

				private:
					static NativeString className;

					UnixStandardInputStream(const UnixStandardInputStream&);
					UnixStandardInputStream& operator =(const UnixStandardInputStream&);

				public:
					UnixStandardInputStream();
					virtual ~UnixStandardInputStream();

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

