#ifndef JCPP_GC_INFO_VARIABLESINFO_H
#define JCPP_GC_INFO_VARIABLESINFO_H

#include "jcpp/gc/info/PointerInfo.h"

namespace jcpp {
	namespace gc {
		namespace info {

			class MethodCallInfo;

			class JCPP_EXPORT VariableInfo : public PointerInfo {
			private:
				jint index;
				MethodCallInfo* methodCallInfo;
			public:
				VariableInfo(MethodCallInfo* methodCallInfo, void** pointer, jint index);

				virtual ~VariableInfo();
			};

		}
	}
}

#endif
