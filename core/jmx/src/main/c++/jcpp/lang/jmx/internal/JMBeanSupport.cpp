#include "jcpp/lang/jmx/internal/JMBeanSupport.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//--------------
			//	Protected
			//--------------

				JMBeanSupport::JMBeanSupport(JObject* resource, JClass* mbeanInterface):JObject(JMBeanSupport::getClazz()){

				}

				JMBeanSupport::JMBeanSupport(JObject* resource, JClass* mbeanInterface, JClass* clazz):JObject(clazz){

				}

			//--------------
			//	Public
			//--------------


				JObject* JMBeanSupport::getResource(){
					return null;
				}

				JObjectName* JMBeanSupport::preRegister(JMBeanServer* server, JObjectName* name){
					return null;
				}

				void JMBeanSupport::preRegister2(JMBeanServer* server, JObjectName* name){

				}

				void JMBeanSupport::postRegister(jbool registrationDone){

				}

				JObject* JMBeanSupport::invoke(JString* operation, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
					return null;
				}

				JObject* JMBeanSupport::getAttribute(JString* attribute){
					return null;
				}

				void JMBeanSupport::setAttribute(JAttribute* attribute){

				}

				JMBeanSupport::~JMBeanSupport(){
				}
			}
		}
	}
}
