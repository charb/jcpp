#ifndef JCPP_NATIVE_UNIXOS_IO_UNIXSTANDARDOUTPUTSTREAM
#define JCPP_NATIVE_UNIXOS_IO_UNIXSTANDARDOUTPUTSTREAM

#include "jcpp/native/api/io/NativeOutputStream.h"
#include "jcpp/native/api/NativeString.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				class JCPP_EXPORT UnixStandardOutputStream: public NativeOutputStream {

				private:
					static NativeString className;

					int stdFD;

					UnixStandardOutputStream(const UnixStandardOutputStream&);
					UnixStandardOutputStream& operator =(const UnixStandardOutputStream&);

				public:
					UnixStandardOutputStream(jbool out);
					virtual ~UnixStandardOutputStream();

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
