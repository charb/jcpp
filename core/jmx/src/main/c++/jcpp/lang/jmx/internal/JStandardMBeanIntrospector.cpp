#include "jcpp/lang/jmx/internal/JStandardMBeanIntrospector.h"
#include "jcpp/util/JHashMap.h"



namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//---------
			//	Private
			//---------
				JStandardMBeanIntrospector* JStandardMBeanIntrospector::instance =  new JStandardMBeanIntrospector();
				JHashMap* JStandardMBeanIntrospector::perInterfaceMap = new JHashMap();

			//----------
			//	Protected
			//----------
				JStandardMBeanIntrospector* JStandardMBeanIntrospector::getInstance(){
					return null;
				}

				JStandardMBeanIntrospector::JStandardMBeanIntrospector():JMBeanIntrospector(JStandardMBeanIntrospector::getClazz()){
				}

				JHashMap* JStandardMBeanIntrospector::getPerInterfaceMap(){
					return null;
				}

				JMBeanAnalyzer* JStandardMBeanIntrospector::getAnalyzer(JClass* mbeanInterface){
					return null;
				}

				JPrimitiveObjectArray* JStandardMBeanIntrospector::getSignature(JObject* m){
					return null;
				}

				void JStandardMBeanIntrospector::checkMethod(JObject* m){

				}

				JObject* JStandardMBeanIntrospector::mFrom(JObject* m){
					return null;
				}

				JClass* JStandardMBeanIntrospector::getGenericReturnType(JObject* m){
					return null;
				}

				JPrimitiveObjectArray* JStandardMBeanIntrospector::getGenericParameterTypes(JObject* m){
					return null;
				}

				JString* JStandardMBeanIntrospector::getName(JObject* m){
					return null;
				}

				JObject* JStandardMBeanIntrospector::invokeM2(JObject* m, JObject* target, JPrimitiveObjectArray* args, JObject* cookie){
					return null;
				}


				JStandardMBeanIntrospector::~JStandardMBeanIntrospector(){

				}
			}
		}
	}
}
