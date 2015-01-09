#ifndef JCPP_NATIVE_WINDOWS_LIBRARY_WINDOWSLIBRARYFACTORY
#define JCPP_NATIVE_WINDOWS_LIBRARY_WINDOWSLIBRARYFACTORY

#include "jcpp/native/api/library/NativeLibraryFactory.h"

using namespace jcpp::native::api::library;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace library {
				class JCPP_EXPORT WindowsLibraryFactory : public NativeLibraryFactory {
				public:
					WindowsLibraryFactory();

					virtual ~WindowsLibraryFactory();

					virtual NativeLibrary * createNativeLibrary(const NativeString& path);
				};
			}
		}
	}
}

#endif
