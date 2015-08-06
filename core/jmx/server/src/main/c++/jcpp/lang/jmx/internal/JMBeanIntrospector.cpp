#include "jcpp/lang/jmx/internal/JMBeanIntrospector.h"
#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/jmx/internal/JPerInterface.h"
#include "jcpp/lang/jmx/internal/JIntrospector.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JException.h"


#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInteger.h"

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

					JPerInterface* JMBeanIntrospector::getPerInterface(JClass* mbeanInterface){
						JHashMap* map = getPerInterfaceMap();
						synchronized(map,
							JPerInterface* pi = dynamic_cast<JPerInterface*>(map->get(mbeanInterface));
							if(pi == null){
								try{
									JMBeanAnalyzer* analyzer = getAnalyzer(mbeanInterface);
									pi = new JPerInterface(mbeanInterface, this, analyzer);
									map->put(mbeanInterface, pi);
								} catch (JException* x){
									throw JIntrospector::throwException(mbeanInterface, x);
								}
							}
							return pi;
						)
					}

					jbool JMBeanIntrospector::consistent(JObject* getter, JObject* setter){
						return (getter == null || setter == null || getGenericReturnType(getter)->equals(getGenericParameterTypes(setter)->get(0)));
					}

					JObject* JMBeanIntrospector::invokeM(JObject* m, JObject* target, JPrimitiveObjectArray* args, JObject* cookie){
						try{
							return invokeM2(m, target, args, cookie);
						} catch (JException* e){
							throw e;
						}
					}

					void JMBeanIntrospector::invokeSetter(JString* name, JObject* setter, JObject* target, JObject* arg, JObject* cookie){
						try{
							JPrimitiveObjectArray* argArray = new JPrimitiveObjectArray(arg->getClass(), 1);
							argArray->set(0, arg);
							invokeM2(setter, target, argArray, cookie);
						} catch (JException* e){
							throw e;
						}
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
