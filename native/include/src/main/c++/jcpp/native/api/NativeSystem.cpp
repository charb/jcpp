#include "jcpp/native/api/NativeSystem.h"

namespace jcpp {
	namespace native {
		namespace api {

			NativeSystem * NativeSystem::instance = null;

			NativeSystem::NativeSystem() {

			}

			NativeSystem::~NativeSystem() {

			}

			NativeSystem * NativeSystem::getInstance() {
				return instance;
			}

			void NativeSystem::setInstance(NativeSystem * newInstance) {
				instance = newInstance;
			}

		}
	}
}
