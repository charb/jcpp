
#include "jcpp/lang/jmx/internal/JMBeanServerDelegate.h";


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				JMBeanServerDelegate::JMBeanServerDelegate():JObject(JMBeanServerDelegate::getClazz()){
				}

				JObject* JMBeanServerDelegate::invoke(JString* actionName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
					//TODO
					return null;
				}

				JMBeanInfo* JMBeanServerDelegate::getJMBeanInfo(){
					//TODO
					return null;
				}

				JObject* JMBeanServerDelegate::getAttribute(JString* jattribute){
					//TODO
					return null;
				}

				void JMBeanServerDelegate::setJAttribute(JAttribute* attribute){
					//TODO
				}

				void JMBeanServerDelegate::postRegister(jbool registrationDone){
					//TODO
				}

				JObjectName* JMBeanServerDelegate::preRegister(JMBeanServer* server, JObjectName* name){
					//TODO
					return null;
				}

				JMBeanServerDelegate::~JMBeanServerDelegate(){
				}
			}
		}
	}
}

