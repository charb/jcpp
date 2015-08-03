#include "jcpp/lang/jmx/internal/JDefaultMBeanServerInterceptor.h"
#include "jcpp/lang/jmx/JMBeanRegistration.h"
#include "jcpp/lang/jmx/JObjectName.h"
#include "jcpp/lang/jmx/JMBeanServer.h"
#include "jcpp/lang/jmx/JObjectInstance.h"
#include "jcpp/lang/jmx/JDynamicMBean.h"
#include "jcpp/lang/jmx/internal/JMBeanServerDelegate.h"
#include "jcpp/lang/jmx/internal/JRepository.h"
#include "jcpp/lang/jmx/JAttribute.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/jmx/internal/JIntrospector.h"
#include "jcpp/lang/jmx/internal/JDynamicMBean2.h"
#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JError.h"
#include "jcpp/lang/JAssertionError.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			//----------
			//	Private
			//----------
				JString* JDefaultMBeanInterceptor::getNewMBeanClassName(JObject* mbeanToRegister){
					return mbeanToRegister->getClass()->getName();
				}

				void JDefaultMBeanInterceptor::postRegisterInvoke(JMBeanRegistration* moi, jbool registrationDone, jbool registrationFailed){
					if(registrationFailed && moi->getClazz()->isAssignableFrom(JDynamicMBean2::getClazz()))
						dynamic_cast<JDynamicMBean2*>(moi)->registerFailed();
					try{
						moi->postRegister(registrationDone);
					} catch (JRuntimeException* e){
						throw new JRuntimeException(new JString("RuntimeException thrown in postRegister method"));
					} catch(JError* er){
						throw new JError(new JString("Error thrown in postRegister method"));
					}
				}

				JObjectName* JDefaultMBeanInterceptor::preRegisterInvoke(JMBeanRegistration* moi, JObjectName* name, JMBeanServer* mbs){
					JObjectName* newName;
					try{
						newName = moi->preRegister(mbs, name);
					} catch(JRuntimeException* e){
						throw new JRuntimeException(new JString("RuntimeException thrown in preRegister method"));
					} catch (JError* er){
						throw new JRuntimeException(new JString("Error thrown in preRegister method"));
					} catch (JException* ex){
						throw new JRuntimeException(new JString("Exception thrown in preRegister method"));
					}

					if(newName != null)
						return newName;
					else
						return name;
				}

				JObjectInstance* JDefaultMBeanInterceptor::registerObject(JString* classname, JObject* object, JObjectName* name){
					if(object == null){
						throw new JException(new JString("Exception occured trying to register the MBean"));
					}
					JDynamicMBean* mbean = JIntrospector::makeDynamicMBean(object);
					return registerDynamicMBean(classname, mbean, name);
				}

				JObjectInstance* JDefaultMBeanInterceptor::registerDynamicMBean(JString* classname, JDynamicMBean* mbean, JObjectName* name){

					JObjectName* logicalName = name;

					if(mbean->getClazz()->isAssignableFrom(JMBeanRegistration::getClazz())){
						JMBeanRegistration* reg = dynamic_cast<JMBeanRegistration*>(mbean);
						logicalName = preRegisterInvoke(reg, name, server);
						if(mbean->getClazz()->isAssignableFrom(JDynamicMBean2::getClazz())){
							try{
								dynamic_cast<JDynamicMBean2*>(mbean)->preRegister2(server, logicalName);
							} catch(JException* e){
								postRegisterInvoke(reg, false, false);
								e->printStackTrace();
							}
						}
					}

					JObjectInstance* result;
					if(logicalName != null){
						result = new JObjectInstance();
						internal_addObject(mbean, logicalName);
					} else{
						if(mbean->getClazz()->isAssignableFrom(JMBeanRegistration::getClazz()))
							postRegisterInvoke(dynamic_cast<JMBeanRegistration*>(mbean), false, true);
						throw new JException(new JString("Exception occurred trying to register the MBean"));
					}

					if(mbean->getClazz()->isAssignableFrom(JMBeanRegistration::getClazz()))
						postRegisterInvoke(dynamic_cast<JMBeanRegistration*>(mbean), true, false);

					return result;
				}


				void JDefaultMBeanInterceptor::internal_addObject(JDynamicMBean* object, JObjectName* logicalName){
					try{
						repository->addMBean(object, logicalName);
					} catch(JException* e){
						if(object->getClazz()->isAssignableFrom(JMBeanRegistration::getClazz())){
							postRegisterInvoke(dynamic_cast<JMBeanRegistration*>(object), false, true);
						}
						throw e;
					}
				}
			//--------------
			//	Protected
			//-------------
				JDynamicMBean* JDefaultMBeanInterceptor::getMBean(JObjectName* name){
					if(name == null){
						throw new JException(new JString("Object name cannot be null, Exception occurred trying ..."));
					}
					JDynamicMBean* obj = null;
					obj = repository->retrieve(name);
					if(obj == null){
						throw new JException(name->toString());
					}
					return obj;
				}
			//--------------
			//	Public
			//--------------
				JDefaultMBeanInterceptor::JDefaultMBeanInterceptor(JMBeanServer* outer, JMBeanServerDelegate* delegate, JRepository* repository)
				:JObject(JDefaultMBeanInterceptor::getClazz()){
					server = null;
					if(outer == null)
						throw new JIllegalArgumentException(new JString("outer MBeanServer cannot be null"));
					if(delegate == null)
					throw new JIllegalArgumentException(new JString("MBeanServerDelegate cannot be null"));

					if(repository == null)
						throw new JIllegalArgumentException(new JString("Repository cannot be null"));
					this->server = outer;
					this->repository= repository;
					this->domain = repository->getDefaultDomain();
				}

				JObjectInstance* JDefaultMBeanInterceptor::registerMBean(JObject* object, JObjectName* name){
					JClass* theClass = object->getClass();

					JIntrospector::checkCompliance(theClass);

					JString* infoClassName = getNewMBeanClassName(object);

					return registerObject(infoClassName, object, name);
				}

				JObject* JDefaultMBeanInterceptor::invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
					JDynamicMBean* instance = getMBean(name);
					return instance->invoke(operationName, params, signature);
				}

				JObject* JDefaultMBeanInterceptor::getAttribute(JObjectName* name, JString* attribute){
					if(name == null){
						throw new JException(new JString("Exception occurred trying to invoke the getter on the MBean"));
					}
					if(attribute == null){
						throw new JException(new JString("Exception occurred trying to invoke the getter on the MBean"));
					}

					JDynamicMBean* instance = getMBean(name);

					try{
						return instance->getAttribute(attribute);
					} catch (JException* e){
						throw e;
					} catch(JThrowable* t){
						throw new JAssertionError();
					}
				}

				void JDefaultMBeanInterceptor::setAttribute(JObjectName* name, JAttribute* attribute){
					if(name == null){
						throw new JException(new JString("Exception occurred trying to invoke the setter on the MBean"));
					}
					if(attribute == null){
						throw new JException(new JString("Exception occurred trying to invoke the setter on the MBean"));
					}

					JDynamicMBean* instance = getMBean(name);

					try{
						instance->setAttribute(attribute);
					} catch (JException* t){
						throw new JAssertionError();
					}
				}




				JDefaultMBeanInterceptor::~JDefaultMBeanInterceptor(){

				}
			}
		}
	}
}
