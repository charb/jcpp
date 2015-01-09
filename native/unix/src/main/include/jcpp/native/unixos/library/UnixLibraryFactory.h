#ifndef JCPP_NATIVE_UNIXOS_LIBRARY_UNIXLIBRARYFACTORY
#define JCPP_NATIVE_UNIXOS_LIBRARY_UNIXLIBRARYFACTORY

#include "jcpp/native/api/library/NativeLibraryFactory.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"

using jcpp::native::unixos::nthread::UnixMutex;
using namespace jcpp::native::api::library;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace library {
				class JCPP_EXPORT UnixLibraryFactory : public NativeLibraryFactory {

				private:
					UnixMutex errorMutex;

				public:
					UnixLibraryFactory();

					virtual ~UnixLibraryFactory();

					virtual NativeLibrary * createNativeLibrary(const NativeString& path);
				};
			}
		}
	}
}

#endif
