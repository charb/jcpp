#include "jcpp/lang/jmx/internal/JMBeanSupport.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/jmx/internal/JMBeanIntrospector.h"
#include "jcpp/lang/jmx/JMBeanRegistration.h"
#include "jcpp/lang/jmx/internal/JPerInterface.h"
#include "jcpp/lang/jmx/JAttribute.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//--------------
			//	Private
			//--------------

			void JMBeanSupport::init(JObject* resource, JClass* mbeanInterface){
				if(mbeanInterface == null)
					throw new JException(new JString("Null MBean interface"));
				if(!mbeanInterface->isAssignableFrom(resource->getClass())){
					JString* msg = new JString("Resource class ");
					msg->concat(resource->getClass()->getName());
					msg->concat(new JString(" is not an instance of "));
					msg->concat(mbeanInterface->getName());
					throw new JException(msg);
				}
				this->resource = resource;
				JMBeanIntrospector* introspector = getMBeanIntrospector();
				this->perInterface = introspector->getPerInterface(mbeanInterface);
			}

			//--------------
			//	Protected
			//--------------

				JMBeanSupport::JMBeanSupport(JObject* resource, JClass* mbeanInterface):JObject(JMBeanSupport::getClazz()){
					init(resource, mbeanInterface);
				}

				JMBeanSupport::JMBeanSupport(JObject* resource, JClass* mbeanInterface, JClass* clazz):JObject(clazz){
					init(resource, mbeanInterface);
				}

			//--------------
			//	Public
			//--------------


				JObject* JMBeanSupport::getResource(){
					return resource;
				}

				JObjectName* JMBeanSupport::preRegister(JMBeanServer* server, JObjectName* name){
					if(resource->getClass()->isAssignableFrom(JMBeanRegistration::getClazz()))
						return dynamic_cast<JMBeanRegistration*>(resource)->preRegister(server, name);
					else
						return name;
				}

				void JMBeanSupport::preRegister2(JMBeanServer* server, JObjectName* name){
					jRegister(server, name);
				}

				void JMBeanSupport::postRegister(jbool registrationDone){
					if(resource->getClass()->isAssignableFrom(JMBeanRegistration::getClazz()))
						return dynamic_cast<JMBeanRegistration*>(resource)->postRegister(registrationDone);
				}

				JObject* JMBeanSupport::invoke(JString* operation, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
					return perInterface->invoke(resource, operation, params, signature, getCookie());
				}

				JObject* JMBeanSupport::getAttribute(JString* attribute){
					return perInterface->getAttribute(resource, attribute, getCookie());
				}

				void JMBeanSupport::setAttribute(JAttribute* attribute){
					JString* name = attribute->getName();
					JObject* value = attribute->getValue();
					perInterface->setAttribute(resource, name, value, getCookie());
				}

				JMBeanSupport::~JMBeanSupport(){
				}
			}
		}
	}
}
