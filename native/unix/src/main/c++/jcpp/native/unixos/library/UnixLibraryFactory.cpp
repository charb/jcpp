#include "jcpp/native/unixos/library/UnixLibraryFactory.h"
#include "jcpp/native/unixos/library/UnixLibrary.h"

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace library {

				UnixLibraryFactory::UnixLibraryFactory() :
						errorMutex() {
				}

				UnixLibraryFactory::~UnixLibraryFactory() {

				}

				NativeLibrary * UnixLibraryFactory::createNativeLibrary(const NativeString& path) {
					return new UnixLibrary(&errorMutex, path);
				}
			}
		}
	}
}
