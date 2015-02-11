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
				NativeString* name;

				ObjectInfo* objectInfo;

				jint parameterCount;
				ParameterInfo** parameterInfos;

				jint variableCount;
				VariableInfo** variableInfos;

				void addParameterInfo(jint index, ParameterInfo* parameterInfo);
				void addVariableInfo(jint index, VariableInfo* variableInfo);
				void removeVariableInfo(jint index);

			public:
				MethodCallInfo(NativeString* name, ObjectInfo* objectInfo, jint parameterCount, ParameterInfo** parameterInfos, jint variableCount, VariableInfo** variableInfos);

				NativeString* getName() const;

				ObjectInfo* getObjectInfo() const;

				jint getParameterCount() const;
				ParameterInfo** getParameterInfos() const;

				jint getVariableCount() const;
				VariableInfo** geVariableInfos() const;

				virtual ~MethodCallInfo();

				friend class ParameterInfo;
				friend class VariableInfo;
			};

		}
	}
}

#endif
