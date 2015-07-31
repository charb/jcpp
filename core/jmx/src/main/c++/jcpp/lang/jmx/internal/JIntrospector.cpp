#include "jcpp/lang/jmx/internal/JIntrospector.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//----------------
			//	Protected
			//----------------

				JException* JIntrospector::throwException(JClass* notCompliant, JThrowable* cause){
					return null;
				}

			//----------------
			//	public
			//----------------
				void JIntrospector::checkCompliance(JClass* mbeanClass){

				}

				JDynamicMBean* JIntrospector::makeDynamicMBean(JObject* mbean){
					return null;
				}

				JClass* JIntrospector::getStandardMBeanInterface(JClass* baseClass){
					return null;
				}

				JClass* JIntrospector::findMBeanInterface(JClass* aClass, JString* aName){
					return null;
				}

				JClass* JIntrospector::implementsMBean(JClass* c, JString* clName){
					return null;
				}

				JIntrospector::~JIntrospector(){
				}
			}
		}
	}
}
