#include "jcpp/lang/jmx/internal/JMBeanIntrospector.h"
#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JHashMap.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				//-----------
				//	Private
				//-----------
					JPrimitiveObjectArray* JMBeanIntrospector::findConstructors(JClass* c){
						return null;
					}


				//-----------
				//	Protected
				//-----------




					JMBeanIntrospector::JMBeanIntrospector():JObject(JMBeanIntrospector::getClazz()){
					}

					JMBeanIntrospector::JMBeanIntrospector(JClass* clazz): JObject(clazz){
					}

					JPerInterface* JMBeanIntrospector::getPerInterface(JClass* mbeanInterface, JMBeanAnalyzer* analyzer){
						return null;
					}

					jbool JMBeanIntrospector::consistent(JObject* getter, JObject* setter){
						return false;
					}

					JObject* JMBeanIntrospector::invokeM(JObject* m, JObject* target, JPrimitiveObjectArray* args, JObject* cookie){
						return null;
					}

					void JMBeanIntrospector::invokeSetter(JString* name, JObject* setter, JObject* target, JObject* arg, JObject* cookie){

					}



				//-----------
				//	Public
				//-----------

					JMBeanIntrospector::~JMBeanIntrospector(){
					}
			}
		}
	}
}
