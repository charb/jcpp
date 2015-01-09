#include "jcpp/native/api/io/NativeIOFactory.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace io {

				NativeIOFactory * NativeIOFactory::instance = null;

				NativeIOFactory::NativeIOFactory() {
				}

				NativeIOFactory::~NativeIOFactory() {
				}

				NativeIOFactory * NativeIOFactory::getInstance() {
					return instance;
				}

				void NativeIOFactory::setInstance(NativeIOFactory * instance) {
					NativeIOFactory::instance = instance;
				}

			}
		}
	}
}
