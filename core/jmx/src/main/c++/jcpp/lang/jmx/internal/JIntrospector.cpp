#include "jcpp/lang/jmx/internal/JIntrospector.h"
#include "jcpp/lang/jmx/JDynamicMBean.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/jmx/internal/JStandardMBeanSupport.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/util/JList.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//-------------
			//	Private
			//-------------
				JClass* JIntrospector::findMBeanInterface(JClass* aClass, JString* aName){
					JClass* current = aClass;
					while(current != null){
						JPrimitiveObjectArray* interfaces = current->getInterfaces()->toArray();
						jint len = interfaces->size();
						for (jint i = 0; i < len; i++){
							JClass* inter = implementsMBean(dynamic_cast<JClass*>(interfaces->get(i)), aName);
							if(inter != null)
								return inter;
						}
						current = current->getSuperclass();
					}
					return null;
				}

				JClass* JIntrospector::implementsMBean(JClass* c, JString* clName){
					JString* clMBeanName = clName->concat(new JString("MBean"));
					if(c->getName()->equals(clMBeanName)){
						return c;
					}
					JPrimitiveObjectArray* interfaces = c->getInterfaces()->toArray();
					for(jint i = 0; i < interfaces->size(); i++){
						if(dynamic_cast<JClass*>(interfaces->get(i))->getName()->equals(clMBeanName))
							return dynamic_cast<JClass*>(interfaces->get(i));
					}
					return null;
				}
			//----------------
			//	Protected
			//----------------

				JException* JIntrospector::throwException(JClass* notCompliant, JThrowable* cause){
					JString* msg = (new JString("class :"))->concat(notCompliant->getName());
					msg->concat((new JString(" , cause: "))->concat(cause->toString()));
					throw new JException((new JString("JIntrospector::throwException. "))->concat(msg));
				}

			//----------------
			//	public
			//----------------
				void JIntrospector::checkCompliance(JClass* mbeanClass){
					if(JDynamicMBean::getClazz()->isAssignableFrom(mbeanClass))
						return;
					try{
						getStandardMBeanInterface(mbeanClass);
					} catch (JException* e){
					}
				}

				JDynamicMBean* JIntrospector::makeDynamicMBean(JObject* mbean){
					if(mbean->getClass()->isAssignableFrom(JDynamicMBean::getClazz()))
						return dynamic_cast<JDynamicMBean*>(mbean);
					JClass* mbeanClass = mbean->getClass();
					JClass* c = null;
					try{
						c = getStandardMBeanInterface(mbeanClass);
					} catch (JException* e){
						// ignore
					}
					if(c != null)
						return new JStandardMBeanSupport(mbean, dynamic_cast<JClass*>(c));

					checkCompliance(mbeanClass);
					throw new JException(new JString("Not compliant"));	// not reached

				}

				JClass* JIntrospector::getStandardMBeanInterface(JClass* baseClass){
					JClass* current = baseClass;
					JClass* mbeanInterface = null;
					while(current != null){
						mbeanInterface = findMBeanInterface(current, current->getName());
						if(mbeanInterface != null)
							break;
						current = current->getSuperclass();
					}
					if(mbeanInterface != null){
						return mbeanInterface;
					} else{
						JString* msg = ((new JString("class "))->concat(baseClass->getName()))->concat(new JString(" is not a JMX compliant Standard MBean"));
						throw new JException(msg);
					}
				}



				JIntrospector::~JIntrospector(){
				}
			}
		}
	}
}
