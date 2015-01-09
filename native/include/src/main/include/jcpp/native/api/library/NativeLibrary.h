#ifndef JCPP_NATIVE_API_LIBRARY_NATIVELIBRARY
#define JCPP_NATIVE_API_LIBRARY_NATIVELIBRARY

#include "jcpp/native/api/NativeString.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace api {
			namespace library {

				class JCPP_EXPORT NativeLibrary {
				protected:
					NativeString path;

					NativeLibrary(const NativeString& path);

				public:
					virtual ~NativeLibrary();

					/**
					 * Returns the function name
					 */
					virtual void* getFunction(const NativeString& name) const =0;
				};

			}
		}
	}
}

#endif
