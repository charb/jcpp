#ifndef JCPP_NATIVE_API_FILE_NATIVEFILEFACTORY
#define JCPP_NATIVE_API_FILE_NATIVEFILEFACTORY

#include "jcpp/native/api/file/NativeFile.h"

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
			namespace file {

				class JCPP_EXPORT NativeFileFactory {

					friend class jcpp::native::api::NativeFactory;

				private:
					static NativeFileFactory * instance;

				protected:

					NativeFileFactory();

					static NativeFileFactory * getInstance();
					static void setInstance(NativeFileFactory * instance);

				public:
					virtual ~NativeFileFactory();

					/**
					 * Creates a Native File with '.' as its path
					 */
					virtual NativeFile * createNativeFile() = 0;
					/**
					 * Creates a Native File with specified path
					 */
					virtual NativeFile * createNativeFile(const NativeString& path) = 0;
					/**
					 * Creates a Native File with combined path of the parent and child.
					 * Child path should always be a relative path.
					 */
					virtual NativeFile * createNativeFile(const NativeString& parent, const NativeString& child) = 0;

				};

			}
		}
	}
}

#endif
