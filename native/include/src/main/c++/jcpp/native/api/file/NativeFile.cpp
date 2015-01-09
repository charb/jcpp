#include "jcpp/native/api/file/NativeFile.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace file {

				NativeFile::NativeFile() :
						path(".") {
				}

				NativeFile::NativeFile(const NativeString& path) :
						path(path) {
				}

				NativeFile::~NativeFile() {
				}

				jchar NativeFile::pathSeperator() {
#if defined (WIN32)
					return (jchar)';';
#else
					return (jchar) ':';
#endif
				}

				jchar NativeFile::fileSeperator() {
#if defined (WIN32)
					return (jchar)'\\';
#else
					return (jchar) '/';
#endif
				}

				NativeString NativeFile::getPath() const {
					return path;
				}

			}
		}
	}
}
