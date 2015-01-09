#ifndef JCPP_GC_INFO_METHODCALLINFO_H
#define JCPP_GC_INFO_METHODCALLINFO_H

#include "jcpp/native/api/NativeString.h"
#include "jcpp/gc/info/ObjectInfo.h"
#include "jcpp/gc/info/ParameterInfo.h"
#include "jcpp/gc/info/VariableInfo.h"
#include <vector>

using namespace jcpp::native::api;

namespace jcpp {
	namespace gc {
		namespace info {

			class JCPP_EXPORT MethodCallInfo {

			private:
				NativeString name;

				ObjectInfo* objectInfo;

				std::vector<ParameterInfo*> parameterInfos;
				std::vector<VariableInfo*> variableInfos;

				void addParameterInfo(ParameterInfo* parameterInfo);
				void addVariableInfo(VariableInfo* variableInfo);
				void removeVariableInfo(VariableInfo* variableInfo);

			public:
				MethodCallInfo(const char* name, ObjectInfo* objectInfo);

				NativeString getName() const;

				ObjectInfo* getObjectInfo() const;

				std::vector<ParameterInfo*>* getParameterInfos();

				std::vector<VariableInfo*>* geVariableInfos();

				virtual ~MethodCallInfo();

				friend class ParameterInfo;
				friend class VariableInfo;
			};

		}
	}
}

#endif
