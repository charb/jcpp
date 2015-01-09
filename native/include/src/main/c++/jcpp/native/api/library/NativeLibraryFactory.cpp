#include "jcpp/native/api/library/NativeLibraryFactory.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace library {

				NativeLibraryFactory * NativeLibraryFactory::instance = null;

				NativeLibraryFactory::NativeLibraryFactory() {
				}

				NativeLibraryFactory::~NativeLibraryFactory() {
				}

				NativeLibraryFactory * NativeLibraryFactory::getInstance() {
					return instance;
				}

				void NativeLibraryFactory::setInstance(NativeLibraryFactory * instance) {
					NativeLibraryFactory::instance = instance;
				}

			}
		}
	}
}
