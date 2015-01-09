#ifndef JCPP_GC_INFO_PARAMETERSINFO_H
#define JCPP_GC_INFO_PARAMETERSINFO_H

#include "jcpp/gc/info/PointerInfo.h"
#include "jcpp/native/api/NativeString.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {
		namespace info {

			class MethodCallInfo;

			class JCPP_EXPORT ParameterInfo : public PointerInfo {
			private:
				NativeString name;
			public:
				ParameterInfo(MethodCallInfo* methodCallInfo, const char* name, void** pointer);

				virtual ~ParameterInfo();

			};

		}
	}
}

#endif
