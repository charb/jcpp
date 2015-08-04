#include "jcpp/lang/jmx/internal/JStandardMBeanIntrospector.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/jmx/internal/JMBeanAnalyzer.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/util/JArrays.h"


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
					return instance;
				}

				JStandardMBeanIntrospector::JStandardMBeanIntrospector():JMBeanIntrospector(JStandardMBeanIntrospector::getClazz()){
				}

				JHashMap* JStandardMBeanIntrospector::getPerInterfaceMap(){
					return perInterfaceMap;
				}

				JMBeanAnalyzer* JStandardMBeanIntrospector::getAnalyzer(JClass* mbeanInterface){
					return JMBeanAnalyzer::analyzer(mbeanInterface, this);
				}

				JPrimitiveObjectArray* JStandardMBeanIntrospector::getSignature(JObject* m){
					JPrimitiveObjectArray* params = dynamic_cast<JMethod*>(m)->getParameterTypes()->toArray();
					JPrimitiveObjectArray* sig = new JPrimitiveObjectArray(JString::getClazz(), params->size());
					for(jint i = 0; i < params->size(); i++)
						sig->set(i, dynamic_cast<JClass*>(params->get(i))->getName());
					return sig;
				}

				void JStandardMBeanIntrospector::checkMethod(JObject* m){
				}

				JObject* JStandardMBeanIntrospector::mFrom(JObject* m){
					return m;
				}

				JClass* JStandardMBeanIntrospector::getGenericReturnType(JObject* m){
					return dynamic_cast<JMethod*>(m)->getReturnType();
				}

				JPrimitiveObjectArray* JStandardMBeanIntrospector::getGenericParameterTypes(JObject* m){
					return dynamic_cast<JMethod*>(m)->getParameterTypes()->toArray();
				}

				JString* JStandardMBeanIntrospector::getName(JObject* m){
					JSystem::out->println((new JString("implement me"))->concat(this->getClass()->getName()));
					return null;
				}

				JObject* JStandardMBeanIntrospector::invokeM2(JObject* m, JObject* target, JPrimitiveObjectArray* args, JObject* cookie){
					return dynamic_cast<JMethod*>(m)->invoke(target, JArrays::asList(args));
				}


				JStandardMBeanIntrospector::~JStandardMBeanIntrospector(){

				}
			}
		}
	}
}
