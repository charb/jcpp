#include "jcpp/gc/info/MethodCallInfo.h"
#include "jcpp/gc/Stack.h"

namespace jcpp {
	namespace gc {
		namespace info {

			MethodCallInfo::MethodCallInfo(const char* name, ObjectInfo* objectInfo) : name(name), objectInfo(objectInfo), parameterInfos(), variableInfos() {
				Stack::getStack()->methodCallStarted(this);
			}

			void MethodCallInfo::addParameterInfo(ParameterInfo* parameterInfo) {
				parameterInfos.push_back(parameterInfo);
			}

			void MethodCallInfo::addVariableInfo(VariableInfo* variableInfo) {
				variableInfos.push_back(variableInfo);
			}

			void MethodCallInfo::removeVariableInfo(VariableInfo* variableInfo) {
				for (std::vector<VariableInfo*>::iterator it = variableInfos.begin(); it != variableInfos.end(); ++it) {
					if ((*it) == variableInfo) {
						variableInfos.erase(it);
						break;
					}
				}
			}

			NativeString MethodCallInfo::getName() const {
				return name;
			}

			ObjectInfo* MethodCallInfo::getObjectInfo() const {
				return objectInfo;
			}

			std::vector<ParameterInfo*>* MethodCallInfo::getParameterInfos() {
				return &parameterInfos;
			}

			std::vector<VariableInfo*>* MethodCallInfo::geVariableInfos() {
				return &variableInfos;
			}

			MethodCallInfo::~MethodCallInfo() {
				Stack::getStack()->methodCallExiting();
			}

		}
	}
}
