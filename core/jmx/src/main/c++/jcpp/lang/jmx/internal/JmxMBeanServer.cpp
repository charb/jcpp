#include "jcpp/lang/jmx/internal/JmxMBeanServer.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			//----------------
			//	Private
			//----------------


				JObjectName* JmxMBeanServer::cloneObjectName(JObjectName* name){
					return null;
				}

				JAttribute* JmxMBeanServer::cloneAttribute(JAttribute* attribute){
					return null;
				}

				void JmxMBeanServer::init(JString* domain, JMBeanServer* outer, JMBeanServerDelegate* delegate, jbool failLock){
					mbsInterceptor = null;
					//TODO
				}

			//----------------
			//	Public
			//----------------

				JMBeanServerDelegate* JmxMBeanServer::newMBeanServerDelegate(){
					return null;
				}

				JMBeanServer* JmxMBeanServer::newMBeanServer(JString* defaultDomain, JMBeanServer* outer, JMBeanServerDelegate* delegate){
					return null;
				}


				JmxMBeanServer::JmxMBeanServer(JString* domain, JMBeanServer* outer, JMBeanServerDelegate* delegate)
				:JMBeanServer(JmxMBeanServer::getClazz()){
					init(domain, outer, delegate, true);
				}

				JmxMBeanServer::JmxMBeanServer(JString* domain, JMBeanServer* outer, JMBeanServerDelegate* delegate, jbool fairLock)
				:JMBeanServer(JmxMBeanServer::getClazz()){
					init(domain, outer, delegate, fairLock);
				}

				JObjectInstance* JmxMBeanServer::registerMBean(JObject* object, JObjectName* name){
					return null;
				}

				JObject* JmxMBeanServer::invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
					return null;
				}

				JObject* JmxMBeanServer::getAttribute(JObjectName* name, JString* attribute){
					return null;
				}

				void JmxMBeanServer::setAttribute(JObjectName* name, JAttribute* attribute){

				}



				JmxMBeanServer::~JmxMBeanServer(){
				}
			}
		}
	}
}
