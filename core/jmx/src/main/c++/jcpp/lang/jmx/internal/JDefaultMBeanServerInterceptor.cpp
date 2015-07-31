#include "jcpp/lang/jmx/internal/JDefaultMBeanServerInterceptor.h"
#include "jcpp/lang/jmx/JMBeanRegistration.h"
#include "jcpp/lang/jmx/JObjectName.h"
#include "jcpp/lang/jmx/JMBeanServer.h"
#include "jcpp/lang/jmx/JObjectInstance.h"
#include "jcpp/lang/jmx/JDynamicMBean.h"
#include "jcpp/lang/jmx/internal/JMBeanServerDelegate.h"
#include "jcpp/lang/jmx/internal/JRepository.h"
#include "jcpp/lang/jmx/JAttribute.h"



namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			//----------
			//	Private
			//----------
				JString* JDefaultMBeanInterceptor::getNewMBeanClassName(JObject* mbeanToRegister){
					return null;
				}

				void JDefaultMBeanInterceptor::postRegisterInvoke(JMBeanRegistration* moi, jbool registrationDone, jbool registrationFailed){

				}

				JObjectName* JDefaultMBeanInterceptor::preRegisterInvoke(JMBeanRegistration* moi, JObjectName* name, JMBeanServer* mbs){
					return null;
				}

				JObjectInstance* JDefaultMBeanInterceptor::registerObject(JString* classname, JDynamicMBean* mbean, JObjectName* name){
					return null;
				}

				JObjectInstance* JDefaultMBeanInterceptor::registerDynamicMBean(JString* classname, JDynamicMBean* mbean, JObjectName* name){
					return null;
				}

				JObjectName* JDefaultMBeanInterceptor::nonDefaultDomain(JObjectName* name){
					return null;
				}

				void JDefaultMBeanInterceptor::internal_addObject(JDynamicMBean* object, JObjectName* logicalName){

				}
			//--------------
			//	Protected
			//-------------
				JDynamicMBean* JDefaultMBeanInterceptor::getMBean(JObjectName* name){
					return null;
				}
			//--------------
			//	Public
			//--------------
				JDefaultMBeanInterceptor::JDefaultMBeanInterceptor(JMBeanServer* outer, JMBeanServerDelegate* delegate, JRepository* repository)
				:JObject(JDefaultMBeanInterceptor::getClazz()){
					server = null;
				}

				JObjectInstance* JDefaultMBeanInterceptor::registerMBean(JObject* object, JObjectName* name){
					return null;
				}

				JObject* JDefaultMBeanInterceptor::invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
					return null;
				}

				JObject* JDefaultMBeanInterceptor::getAttribute(JObjectName* name, JString* attribute){
					return null;
				}

				void JDefaultMBeanInterceptor::setAttribute(JObjectName* name, JAttribute* attribute){

				}

				JDefaultMBeanInterceptor::~JDefaultMBeanInterceptor(){

				}
			}
		}
	}
}
