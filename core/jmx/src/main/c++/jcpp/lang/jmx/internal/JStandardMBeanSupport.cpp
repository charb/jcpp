#include "jcpp/lang/jmx/internal/JStandardMBeanSupport.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//------
			//	Protected
			//-----

				JMBeanIntrospector* JStandardMBeanSupport::getMBeanIntrospector(){
					return null;
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

				}

				void JStandardMBeanSupport::jRegister(JMBeanServer* mbs, JObjectName* name){

				}

				void JStandardMBeanSupport::unregister(){

				}

				JStandardMBeanSupport::~JStandardMBeanSupport(){
				}

			}
		}
	}
}
