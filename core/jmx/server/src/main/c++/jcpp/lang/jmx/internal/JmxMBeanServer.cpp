#include "jcpp/lang/jmx/internal/JmxMBeanServer.h"
#include "jcpp/lang/jmx/internal/JRepository.h"
#include "jcpp/lang/jmx/internal/JDefaultMBeanServerInterceptor.h"
#include "jcpp/lang/jmx/JObjectName.h"
#include "jcpp/lang/jmx/JAttribute.h"
#include "jcpp/lang/jmx/internal/JMBeanServerInterceptor.h"



namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			//----------------
			//	Private
			//----------------


				JObjectName* JmxMBeanServer::cloneObjectName(JObjectName* name){
					if(name != null){
						return JObjectName::getInstance(name);
					}
					return name;
				}

				JAttribute* JmxMBeanServer::cloneAttribute(JAttribute* attribute){
					if(attribute != null){
						if(!attribute->getClass()->equals(JAttribute::getClazz())){
							return new JAttribute(attribute->getName(), attribute->getValue());
						}
					}
					return attribute;
				}

				void JmxMBeanServer::init(JString* domain, JMBeanServer* outer, jbool fairLock){
					mbsInterceptor = null;
					if(outer == null)
						outer = this;
					JRepository* repository = new JRepository(domain, fairLock);
					this->mbsInterceptor = new JDefaultMBeanServerInterceptor(outer, repository);
				}

			//----------------
			//	Public
			//----------------



				JMBeanServer* JmxMBeanServer::newMBeanServer(JString* defaultDomain, JMBeanServer* outer){
					jbool fairLock = DEFAULT_FAIR_LOCK_POLICY;
					return new JmxMBeanServer(defaultDomain, outer, fairLock);
				}


				JmxMBeanServer::JmxMBeanServer(JString* domain, JMBeanServer* outer)
				:JObject(JmxMBeanServer::getClazz()){
					init(domain, outer, true);
				}

				JmxMBeanServer::JmxMBeanServer(JString* domain, JMBeanServer* outer, jbool fairLock)
				:JObject(JmxMBeanServer::getClazz()){
					init(domain, outer, fairLock);
				}

				JObjectInstance* JmxMBeanServer::registerMBean(JObject* object, JString* name){
					JObjectName* objName = new JObjectName(name);
					return mbsInterceptor->registerMBean(object, cloneObjectName(objName));
				}

				JObject* JmxMBeanServer::invoke(JString* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
					JObjectName* objName = new JObjectName(name);
					return mbsInterceptor->invoke(cloneObjectName(objName), operationName, params, signature);
				}

				JObject* JmxMBeanServer::getAttribute(JString* name, JString* attribute){
					JObjectName* objName = new JObjectName(name);
					return mbsInterceptor->getAttribute(cloneObjectName(objName), attribute);
				}

				void JmxMBeanServer::setAttribute(JString* name, JAttribute* attribute){
					JObjectName* objName = new JObjectName(name);
					mbsInterceptor->setAttribute(cloneObjectName(objName), cloneAttribute(attribute));
				}



				JmxMBeanServer::~JmxMBeanServer(){
				}


			}
		}
	}
}
