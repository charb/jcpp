#ifndef JCPP_NATIVE_UNIXOS_IO_UNIXFILEINPUTSTREAM
#define JCPP_NATIVE_UNIXOS_IO_UNIXFILEINPUTSTREAM

#include "jcpp/native/api/io/NativeFileInputStream.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/unixos/io/UnixFileDescriptor.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				class JCPP_EXPORT UnixFileInputStream: public NativeFileInputStream {

				private:
					static NativeString className;

					UnixFileDescriptor fileDescriptor;

					UnixFileInputStream(const UnixFileInputStream&);
					UnixFileInputStream& operator =(const UnixFileInputStream&);

				public:
					UnixFileInputStream(const NativeString& path);
					UnixFileInputStream(const UnixFileDescriptor& fileDescriptor);
					virtual ~UnixFileInputStream();

					virtual NativeFileDescriptor * getNativeFileDescriptor();

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

