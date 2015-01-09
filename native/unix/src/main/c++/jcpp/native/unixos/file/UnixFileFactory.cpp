#include "jcpp/native/unixos/file/UnixFileFactory.h"
#include "jcpp/native/unixos/file/UnixFile.h"

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace file {

				UnixFileFactory::UnixFileFactory() {
				}

				UnixFileFactory::~UnixFileFactory() {

				}

				NativeFile * UnixFileFactory::createNativeFile() {
					return new UnixFile();
				}

				NativeFile * UnixFileFactory::createNativeFile(const NativeString& path) {
					return new UnixFile(path);
				}

				NativeFile * UnixFileFactory::createNativeFile(const NativeString& parent, const NativeString& child) {
					return new UnixFile(parent, child);
				}

			}
		}
	}
}
