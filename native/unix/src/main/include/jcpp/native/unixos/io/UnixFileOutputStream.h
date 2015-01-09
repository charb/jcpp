#ifndef JCPP_NATIVE_UNIXOS_IO_UNIXFILEOUTPUTSTREAM
#define JCPP_NATIVE_UNIXOS_IO_UNIXFILEOUTPUTSTREAM

#include "jcpp/native/api/io/NativeFileOutputStream.h"
#include "jcpp/native/api/NativeString.h"
#include "jcpp/native/unixos/io/UnixFileDescriptor.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				class JCPP_EXPORT UnixFileOutputStream: public NativeFileOutputStream {

				private:
					static NativeString className;

					UnixFileDescriptor fileDescriptor;

					UnixFileOutputStream(const UnixFileOutputStream&);
					UnixFileOutputStream& operator =(const UnixFileOutputStream&);

				public:
					UnixFileOutputStream(const NativeString& path, jbool append);
					UnixFileOutputStream(const UnixFileDescriptor& fileDescriptor);
					virtual ~UnixFileOutputStream();

					virtual NativeFileDescriptor * getNativeFileDescriptor();

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
