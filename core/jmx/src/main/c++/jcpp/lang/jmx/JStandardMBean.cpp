#include "jcpp/lang/jmx/JStandardMBean.h";


namespace jcpp{
	namespace lang{
		namespace jmx{
		//-------------
		//	Private
		//-------------
			void JStandardMBean::construct(JObject* implementation, JClass* mbeanInterface, jbool nullImplementationAllowed){

			}

		//-------------
		//	Public
		//-------------
			JStandardMBean::JStandardMBean(JObject* implementation, JClass* mbeanInterface):JObject(JStandardMBean::getClazz()){

			}

			void JStandardMBean::postRegister(jbool registrationDone){

			}

			JObjectName* JStandardMBean::preRegister(JMBeanServer* server, JObjectName* name){
				return null;
			}

			JObject* JStandardMBean::invoke(JString* actionName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
				return null;
			}

			JMBeanInfo* JStandardMBean::getMBeanInfo(){
				return null;
			}

			JObject* JStandardMBean::getAttribute(JString* attribute){
				return null;
			}

			void JStandardMBean::setAttribute(JAttribute* attribute){

			}


			JStandardMBean::~JStandardMBean(){
			}

		}
	}
}
