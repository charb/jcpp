#include "jcpp/native/api/file/NativeFileFactory.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace file {

				NativeFileFactory * NativeFileFactory::instance = null;

				NativeFileFactory::NativeFileFactory() {
				}

				NativeFileFactory::~NativeFileFactory() {
				}

				NativeFileFactory * NativeFileFactory::getInstance() {
					return instance;
				}

				void NativeFileFactory::setInstance(NativeFileFactory * instance) {
					NativeFileFactory::instance = instance;
				}

			}
		}
	}
}
