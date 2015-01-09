#include "jcpp/native/windows/file/WindowsFileFactory.h"
#include "jcpp/native/windows/file/WindowsFile.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace file {

				WindowsFileFactory::WindowsFileFactory() {
				}

				WindowsFileFactory::~WindowsFileFactory() {

				}

				NativeFile * WindowsFileFactory::createNativeFile() {
					return new WindowsFile();
				}

				NativeFile * WindowsFileFactory::createNativeFile(const NativeString& path) {
					return new WindowsFile(path);
				}

				NativeFile * WindowsFileFactory::createNativeFile(const NativeString& parent, const NativeString& child) {
					return new WindowsFile(parent, child);
				}

			}
		}
	}
}
