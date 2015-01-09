#ifndef JCPP_NATIVE_UNIXOS_UNIXSYSTEM
#define JCPP_NATIVE_UNIXOS_UNIXSYSTEM

#include "jcpp/native/api/NativeSystem.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"

using namespace jcpp::native::api;
using namespace jcpp::native::unixos::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {

			class JCPP_EXPORT UnixSystem: public NativeSystem {

			private:
				UnixMutex mutex;
				NativeString lineSeparatorString;

			public:
				UnixSystem();
				virtual ~UnixSystem();

				virtual jlong currentTimeMillis();

				virtual void getEnv(std::map<NativeString, NativeString>& env);

				virtual NativeString getEnv(const NativeString& envVar);

				virtual NativeString lineSeparator();

			};

		}
	}
}

#endif
