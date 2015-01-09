#include "jcpp/native/windows/library/WindowsLibraryFactory.h"
#include "jcpp/native/windows/library/WindowsLibrary.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace library {

				WindowsLibraryFactory::WindowsLibraryFactory() {
				}

				WindowsLibraryFactory::~WindowsLibraryFactory() {

				}

				NativeLibrary * WindowsLibraryFactory::createNativeLibrary(const NativeString& path){
					return new WindowsLibrary(path);
				}
			}
		}
	}
}
