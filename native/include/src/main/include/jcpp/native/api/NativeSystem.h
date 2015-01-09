#ifndef JCPP_NATIVE_API_NATIVESYSTEM
#define JCPP_NATIVE_API_NATIVESYSTEM

#include <map>
#include "jcpp/native/api/NativeString.h"

namespace jcpp {
	namespace native {
		namespace api {
			class NativeFactory;
		}
	}
}

namespace jcpp {
	namespace native {
		namespace api {

			class JCPP_EXPORT NativeSystem {

				friend class jcpp::native::api::NativeFactory;

			private:
				static NativeSystem * instance;

			protected:
				NativeSystem();

				static NativeSystem * getInstance();
				static void setInstance(NativeSystem * instance);
			public:
				virtual ~NativeSystem();

				virtual jlong currentTimeMillis() = 0;

				virtual void getEnv(std::map<NativeString, NativeString>& env) = 0;

				virtual NativeString getEnv(const NativeString& envVar) = 0;

				virtual NativeString lineSeparator() = 0;

			};

		}
	}
}

#endif
