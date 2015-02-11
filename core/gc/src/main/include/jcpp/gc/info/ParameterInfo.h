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
			public:
				ParameterInfo(MethodCallInfo* methodCallInfo, void** pointer, jint index);

				virtual ~ParameterInfo();

			};

		}
	}
}

#endif
