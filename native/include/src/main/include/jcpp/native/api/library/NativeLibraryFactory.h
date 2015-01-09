#ifndef JCPP_NATIVE_API_LIBRARY_NATIVELIBRARYFACTORY
#define JCPP_NATIVE_API_LIBRARY_NATIVELIBRARYFACTORY

#include "jcpp/native/api/library/NativeLibrary.h"

namespace jcpp {
	namespace native {
		namespace api {
			class NativeFactory;
		}
	}
}

namespace jcpp {
	namespace native {
		namespace api {
			namespace library {

				class JCPP_EXPORT NativeLibraryFactory {

					friend class jcpp::native::api::NativeFactory;

				private:
					static NativeLibraryFactory * instance;

				protected:

					NativeLibraryFactory();

					static NativeLibraryFactory * getInstance();
					static void setInstance(NativeLibraryFactory * instance);

				public:
					virtual ~NativeLibraryFactory();

					/**
					 * Creates and load a Native Library with specified path
					 */
					virtual NativeLibrary * createNativeLibrary(const NativeString& path) = 0;
				};

			}
		}
	}
}

#endif
