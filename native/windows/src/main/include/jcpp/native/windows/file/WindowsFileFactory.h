#ifndef JCPP_NATIVE_WINDOWS_FILE_WINDOWSFILEFACTORY
#define JCPP_NATIVE_WINDOWS_FILE_WINDOWSFILEFACTORY

#include "jcpp/native/api/file/NativeFileFactory.h"

using namespace jcpp::native::api::file;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace file {

				class JCPP_EXPORT WindowsFileFactory : public NativeFileFactory {

				public:
					WindowsFileFactory();
					virtual ~WindowsFileFactory();

					virtual NativeFile * createNativeFile();
					virtual NativeFile * createNativeFile(const NativeString& path);
					virtual NativeFile * createNativeFile(const NativeString& parent, const NativeString& child);

				};

			}
		}
	}
}

#endif
