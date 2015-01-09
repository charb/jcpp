#include "jcpp/native/unixos/UnixSystem.h"
#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

#include <stdlib.h>

using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {

			UnixSystem::UnixSystem() :
					mutex(), lineSeparatorString("\n") {
			}

			UnixSystem::~UnixSystem() {

			}

			jlong UnixSystem::currentTimeMillis() {
				return UnixUtils::getCurrentTimeMillis();
			}

			void UnixSystem::getEnv(std::map<NativeString, NativeString>& env) {
				UnixUtils::getEnv(env);
			}

			NativeString UnixSystem::getEnv(const NativeString& envVar) {
				ScopedLock synchronize(mutex);
				char * value = getenv(envVar.getString().c_str());
				return value ? NativeString(value) : NativeString();
			}

			NativeString UnixSystem::lineSeparator() {
				return lineSeparatorString;
			}

		}
	}
}
