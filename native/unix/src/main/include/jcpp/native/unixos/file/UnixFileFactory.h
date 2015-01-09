#ifndef JCPP_NATIVE_UNIXOS_FILE_UNIXFILEFACTORY
#define JCPP_NATIVE_UNIXOS_FILE_UNIXFILEFACTORY

#include "jcpp/native/api/file/NativeFileFactory.h"

using namespace jcpp::native::api::file;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace file {

				class JCPP_EXPORT UnixFileFactory: public NativeFileFactory {

				public:
					UnixFileFactory();
					virtual ~UnixFileFactory();

					virtual NativeFile * createNativeFile();
					virtual NativeFile * createNativeFile(const NativeString& path);
					virtual NativeFile * createNativeFile(const NativeString& parent, const NativeString& child);

				};

			}
		}
	}
}

#endif
