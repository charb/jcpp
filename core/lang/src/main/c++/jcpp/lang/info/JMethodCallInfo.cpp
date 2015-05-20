#include "jcpp/lang/info/JMethodCallInfo.h"

namespace jcpp {
	namespace lang {
		namespace info {
			JMethodCallInfo::JMethodCallInfo():name(null),objectInfo(null)
			{
				methodObjects = new JArrayList(10);
			}
			JMethodCallInfo::JMethodCallInfo(JString* name, JObjectInfo* objectInfo) :
					name(name), objectInfo(objectInfo){
				methodObjects = new JArrayList(10);
			}

			JString* JMethodCallInfo::getName(){
				return name;
			}

			JObjectInfo* JMethodCallInfo::getObjectInfo(){
				return objectInfo;
			}

			void JMethodCallInfo::addMethodObject(JMethodObjectInfo* methodObjectInfo)
			{
				methodObjects->add(methodObjectInfo);
			}

			JList* JMethodCallInfo::getMethodObjects(){
				return methodObjects;
			}
		}
	}
}
