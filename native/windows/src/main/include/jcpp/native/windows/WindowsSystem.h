#ifndef JCPP_NATIVE_WINDOWS_WINDOWSSYSTEM
#define JCPP_NATIVE_WINDOWS_WINDOWSSYSTEM

#include <map>
#include "jcpp/native/api/NativeSystem.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace windows {

			class JCPP_EXPORT WindowsSystem: public NativeSystem {

			private:
				NativeString lineSeparatorString;

			public:
				WindowsSystem();
				virtual ~WindowsSystem();

				virtual jlong currentTimeMillis();

				virtual void getEnv(std::map<NativeString, NativeString>& env);

				virtual NativeString getEnv(const NativeString& envVar);

				virtual NativeString lineSeparator();

			};

		}
	}
}

#endif
