#include "jcpp/native/windows/io/WindowsIOFactory.h"
#include "jcpp/native/windows/io/WindowsFileInputStream.h"
#include "jcpp/native/windows/io/WindowsFileOutputStream.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				WindowsIOFactory::WindowsIOFactory() :
						standardInputStream(), standardOutputStream(true), standardErrorStream(false) {
				}

				WindowsIOFactory::~WindowsIOFactory() {
				}

				NativeInputStream * WindowsIOFactory::getStandardInputStream() {
					return &standardInputStream;
				}

				NativeOutputStream * WindowsIOFactory::getStandardOutputStream() {
					return &standardOutputStream;
				}

				NativeOutputStream * WindowsIOFactory::getStandardErrorStream() {
					return &standardErrorStream;
				}

				NativeFileInputStream * WindowsIOFactory::createFileInputStream(const NativeString& path) {
					return new WindowsFileInputStream(path);
				}

				NativeFileOutputStream * WindowsIOFactory::createFileOutputStream(const NativeString& path, jbool append) {
					return new WindowsFileOutputStream(path, append);
				}

			}
		}
	}
}
