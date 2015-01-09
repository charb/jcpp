#include "jcpp/native/windows/WindowsSystem.h"
#include "jcpp/native/windows/WindowsUtils.h"

namespace jcpp {
	namespace native {
		namespace windows {

			WindowsSystem::WindowsSystem() : lineSeparatorString("\r\n") {
			}

			WindowsSystem::~WindowsSystem() {

			}

			jlong WindowsSystem::currentTimeMillis() {
				return WindowsUtils::getCurrentTimeMillis();
			}

			void WindowsSystem::getEnv(std::map<NativeString, NativeString>& env) {
				WindowsUtils::getEnv(env);
			}

			NativeString WindowsSystem::getEnv(const NativeString& envVar) {
				std::string strEnvVar = envVar.getString();
				int length = GetEnvironmentVariable(strEnvVar.c_str(), NULL, 0);

				if (length == 0) {
					return NativeString();
				}

				char * buffer = new char[length];
				GetEnvironmentVariable(strEnvVar.c_str(), buffer, length);

				return NativeString(buffer);
			}

			NativeString WindowsSystem::lineSeparator() {
				return lineSeparatorString;
			}
		}
	}
}
