#include "jcpp/lang/jmx/internal/JIntrospector.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//----------------
			//	Private
			//-----------------

				jbool JIntrospector::equals(JObject* x, JObject* y){
					return false;
				}

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


				JObject* JIntrospector::annotationToField(JObject* x){
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
