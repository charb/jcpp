#include "jcpp/lang/jmx/internal/JStandardMBeanSupport.h"
#include "jcpp/lang/jmx/internal/JStandardMBeanIntrospector.h"
#include "jcpp/lang/JSystem.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//------
			//	Protected
			//-----

				JMBeanIntrospector* JStandardMBeanSupport::getMBeanIntrospector(){
					return JStandardMBeanIntrospector::getInstance();
				}

				JObject* JStandardMBeanSupport::getCookie(){
					return null;
				}

			//--------
			//	Public
			//--------
				JStandardMBeanSupport::JStandardMBeanSupport(JObject* resource, JClass* mbeanInterface): JMBeanSupport(resource, mbeanInterface, JStandardMBeanSupport::getClazz()){
				}

				void JStandardMBeanSupport::registerFailed(){
					JSystem::out->println((new JString("implement me"))->concat(this->getClass()->getName()));
				}

				void JStandardMBeanSupport::jRegister(JMBeanServer* mbs, JObjectName* name){
					JSystem::out->println((new JString("implement me"))->concat(this->getClass()->getName()));
				}

				void JStandardMBeanSupport::unregister(){
					JSystem::out->println((new JString("implement me"))->concat(this->getClass()->getName()));
				}

				JStandardMBeanSupport::~JStandardMBeanSupport(){
				}

			}
		}
	}
}
