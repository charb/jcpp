#include "jcpp/lang/jmx/internal/JMBeanIntrospector.h"
#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JHashMap.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//------------
			//	JMBeanInfoMaker
			//------------
				JMBeanIntrospector::JMBeanInfoMaker::JMBeanInfoMaker():JObject(JMBeanIntrospector::getClazz()){
					attrs = JUtil::newList();
					ops = JUtil::newList();
				}

				JMBeanInfo* JMBeanIntrospector::JMBeanInfoMaker::makeMBeanInfo(JClass* mbeanInterface, JString* description){
					return null;
				}

				void JMBeanIntrospector::JMBeanInfoMaker::visitAttribute(JString* attributeName, JObject* getter, JObject* setter){

				}

				void JMBeanIntrospector::JMBeanInfoMaker::visitOperation(JString* operationName, JObject* operation){

				}

				JMBeanIntrospector::JMBeanInfoMaker::~JMBeanInfoMaker(){

				}

				//-----------
				//	Private
				//-----------
					JPrimitiveObjectArray* JMBeanIntrospector::findConstructors(JClass* c){
						return null;
					}

					JMBeanInfo* JMBeanIntrospector::makeInterfaceMBeanInfo(JClass* mbeanInterface, JMBeanAnalyzer* analyzer){
						return null;
					}

				//-----------
				//	Protected
				//-----------

					JPerInterface* JMBeanIntrospector::getPerInterface(JClass* mbeanInterface, JMBeanAnalyzer* analyzer){
						return null;
					}

					jbool JMBeanIntrospector::consistent(JObject* getter, JObject* setter){
						return false;
					}

					JMBeanInfo* JMBeanIntrospector::getMBeanInfo(JObject* resource, JPerInterface* perInterface){
						return null;
					}

					JMBeanInfo* JMBeanIntrospector::getClassMBeanInfo(JClass* resourceClass, JPerInterface* perInterface){
						return null;
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
