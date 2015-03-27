#include "jcpp/gc/info/MethodCallInfo.h"
#include "jcpp/gc/Stack.h"

namespace jcpp {
	namespace gc {
		namespace info {

			MethodCallInfo::MethodCallInfo(NativeString* name, ObjectInfo* objectInfo, jint parameterCount, ParameterInfo** parameterInfos, jint variableCount, VariableInfo** variableInfos) :
					name(name), objectInfo(objectInfo), parameterCount(parameterCount), parameterInfos(parameterInfos), variableCount(variableCount), variableInfos(variableInfos) {
				if(parameterCount > 0) {
					for(jint parameterIndex = 0; parameterIndex < parameterCount; parameterIndex++) {
						parameterInfos[parameterIndex] = 0;
					}
				}
				for(jint variableIndex = 0; variableIndex < variableCount; variableIndex++) {
					variableInfos[variableIndex] = 0;
				}
				Stack::getStack()->methodCallStarted(this);
			}

			void MethodCallInfo::addParameterInfo(jint index, ParameterInfo* parameterInfo) {
				parameterInfos[index] = parameterInfo;
			}

			void MethodCallInfo::addVariableInfo(jint index, VariableInfo* variableInfo) {
				variableInfos[index] = variableInfo;
			}

			void MethodCallInfo::removeVariableInfo(jint index) {
				variableInfos[index] = null;
			}

			NativeString* MethodCallInfo::getName() const {
				return name;
			}

			ObjectInfo* MethodCallInfo::getObjectInfo() const {
				return objectInfo;
			}

			jint MethodCallInfo::getParameterCount() const {
				return parameterCount;
			}

			ParameterInfo** MethodCallInfo::getParameterInfos() const{
				return parameterInfos;
			}

			jint MethodCallInfo::getVariableCount() const {
				return variableCount;
			}

			VariableInfo** MethodCallInfo::getVariableInfos() const {
				return variableInfos;
			}

			MethodCallInfo::~MethodCallInfo() {
				Stack::getStack()->methodCallExiting();
			}

		}
	}
}
