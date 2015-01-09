#include "jcpp/native/api/library/NativeLibrary.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace library {

				NativeLibrary::NativeLibrary(const NativeString& path) :
						path(path) {
				}

				NativeLibrary::~NativeLibrary() {
				}
			}
		}
	}
}
