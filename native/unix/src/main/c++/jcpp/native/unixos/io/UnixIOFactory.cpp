#include "jcpp/native/unixos/io/UnixIOFactory.h"
#include "jcpp/native/unixos/io/UnixFileInputStream.h"
#include "jcpp/native/unixos/io/UnixFileOutputStream.h"

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				UnixIOFactory::UnixIOFactory() :
						standardInputStream(), standardOutputStream(true), standardErrorStream(false) {
				}

				UnixIOFactory::~UnixIOFactory() {
				}

				NativeInputStream * UnixIOFactory::getStandardInputStream() {
					return &standardInputStream;
				}

				NativeOutputStream * UnixIOFactory::getStandardOutputStream() {
					return &standardOutputStream;
				}

				NativeOutputStream * UnixIOFactory::getStandardErrorStream() {
					return &standardErrorStream;
				}

				NativeFileInputStream * UnixIOFactory::createFileInputStream(const NativeString& path) {
					return new UnixFileInputStream(path);
				}

				NativeFileOutputStream * UnixIOFactory::createFileOutputStream(const NativeString& path, jbool append) {
					return new UnixFileOutputStream(path, append);
				}

			}
		}
	}
}
