#include "jcpp/lang/jmx/JMBeanParameterInfo.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			JPrimitiveObjectArray* JMBeanParameterInfo::NO_PARAMS =  new JPrimitiveObjectArray(JMBeanParameterInfo::getClazz(), 0);

			JMBeanParameterInfo::JMBeanParameterInfo(JString* name, JString* description)
				:JMBeanFeatureInfo(name, description, JMBeanParameterInfo::getClazz()){
			}

			JMBeanParameterInfo::~JMBeanParameterInfo(){
			}
		}
	}
}
