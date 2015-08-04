#include "jcpp/lang/jmx/internal/JmxMBeanServer.h"
#include "jcpp/lang/jmx/internal/JRepository.h"
#include "jcpp/lang/jmx/internal/JDefaultMBeanServerInterceptor.h"
#include "jcpp/lang/jmx/JObjectName.h"
#include "jcpp/lang/jmx/JAttribute.h"


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
				:JMBeanServer(JmxMBeanServer::getClazz()){
					init(domain, outer, true);
				}

				JmxMBeanServer::JmxMBeanServer(JString* domain, JMBeanServer* outer, jbool fairLock)
				:JMBeanServer(JmxMBeanServer::getClazz()){
					init(domain, outer, fairLock);
				}

				JObjectInstance* JmxMBeanServer::registerMBean(JObject* object, JObjectName* name){
					return mbsInterceptor->registerMBean(object, cloneObjectName(name));
				}

				JObject* JmxMBeanServer::invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
					return mbsInterceptor->invoke(cloneObjectName(name), operationName, params, signature);
				}

				JObject* JmxMBeanServer::getAttribute(JObjectName* name, JString* attribute){
					return mbsInterceptor->getAttribute(cloneObjectName(name), attribute);
				}

				void JmxMBeanServer::setAttribute(JObjectName* name, JAttribute* attribute){
					mbsInterceptor->setAttribute(cloneObjectName(name), cloneAttribute(attribute));
				}



				JmxMBeanServer::~JmxMBeanServer(){
				}
			}
		}
	}
}
