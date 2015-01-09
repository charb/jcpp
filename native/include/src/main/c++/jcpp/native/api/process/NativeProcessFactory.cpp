#include "jcpp/native/api/process/NativeProcessFactory.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace process {

				NativeProcessFactory * NativeProcessFactory::instance = null;

				NativeProcessFactory::NativeProcessFactory() {
				}

				NativeProcessFactory::~NativeProcessFactory() {
				}

				NativeProcessFactory * NativeProcessFactory::getInstance() {
					return instance;
				}

				void NativeProcessFactory::setInstance(NativeProcessFactory * instance) {
					NativeProcessFactory::instance = instance;
				}

			}
		}
	}
}
