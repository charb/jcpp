#include "jcpp/native/api/net/NativeNetFactory.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				NativeNetFactory * NativeNetFactory::instance = null;

				NativeNetFactory::NativeNetFactory() {
				}

				NativeNetFactory::~NativeNetFactory() {
				}

				NativeNetFactory * NativeNetFactory::getInstance() {
					return instance;
				}

				void NativeNetFactory::setInstance(NativeNetFactory * instance) {
					NativeNetFactory::instance = instance;
				}

			}
		}
	}
}
