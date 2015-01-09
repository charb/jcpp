#ifndef JCPP_NATIVE_UNIXOS_LIBRARY_UNIXLIBRARY
#define JCPP_NATIVE_UNIXOS_LIBRARY_UNIXLIBRARY

#include "jcpp/native/api/library/NativeLibrary.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"

using jcpp::native::unixos::nthread::UnixMutex;
using namespace jcpp::native::api::library;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace library {
				class JCPP_EXPORT UnixLibrary: public NativeLibrary {
				private:
					static NativeString className;

					UnixMutex * errorMutex;
					void* handle;

				public:
					UnixLibrary(UnixMutex * errorMutex, const NativeString& path);

					virtual void* getFunction(const NativeString& name) const;

					virtual ~UnixLibrary();
				};
			}
		}
	}
}

#endif
