#include "jcpp/lang/info/JClassInfo.h"
#include "jcpp/util/JArrayList.h"

using namespace jcpp::util;

namespace jcpp {
	namespace lang {
		namespace info {
			JClassInfo::JClassInfo(JString* _namespaceName, JString* _className, jint statiFieldCount) :
					namespaceName(_namespaceName), className(_className){
				staticFieldInfos = new JArrayList(statiFieldCount);
			}

			JList* JClassInfo::getStaticFieldInfos(){
				return staticFieldInfos;
			}

			JString* JClassInfo::getClassName(){
				return className;
			}

			JString* JClassInfo::getNamespaceName(){
				return namespaceName;
			}

			void JClassInfo::addStaticFieldInfo(JFieldInfo* staticFieldInfo){
				staticFieldInfos->add(staticFieldInfo);
			}


			JClassInfo::~JClassInfo(){

			}
		}
	}
}
