#include "jcpp/lang/jmx/JMBeanFeatureInfo.h"



namespace jcpp{
	namespace lang{
		namespace jmx{

			void JMBeanFeatureInfo::init(JString* name, JString* description){
				this->name = name;
				this->description = description;
			}


			JMBeanFeatureInfo::JMBeanFeatureInfo(JString* name, JString* description, JClass* clazz)
				:JObject(clazz){
				init(name, description);
			}


			JString* JMBeanFeatureInfo::getName(){
				return name;
			}

			JString* JMBeanFeatureInfo::getDescription(){
				return description;
			}



			JMBeanFeatureInfo::~JMBeanFeatureInfo(){
			}

		}
	}
}
