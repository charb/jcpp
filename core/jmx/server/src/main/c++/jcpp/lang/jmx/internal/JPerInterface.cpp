#include "jcpp/lang/jmx/internal/JPerInterface.h"
#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/jmx/internal/JMBeanIntrospector.h"
#include "jcpp/lang/JException.h";
#include "jcpp/lang/JAssertionError.h"
#include "jcpp/util/JCollections.h"
#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/lang/JStringBuilder.h"

#include "jcpp/lang/JSystem.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//------------
			//	initMaps
			//------------
				JPerInterface::InitMaps::InitMaps(JPerInterface* parent):JObject(InitMaps::getClazz()){
					this->parent = parent;
				}

				void JPerInterface::InitMaps::visitAttribute(JString* attributeName, JObject* getter, JObject* setter){
					if(getter != null){
						parent->introspector->checkMethod(getter);
						JObject* old = parent->getters->put(attributeName, getter);
						if(old != null){
							throw new JAssertionError();
						}
					}
					if(setter != null){
						parent->introspector->checkMethod(setter);
						JObject* old = parent->setters->put(attributeName, setter);
						if(old != null){
							throw new JAssertionError();
						}
					}
				}
				void JPerInterface::InitMaps::visitOperation(JString* operationName, JObject* operation){
					parent->introspector->checkMethod(operation);
					JPrimitiveObjectArray* sig = parent->introspector->getSignature(operation);
					MethodAndSig* mas = new MethodAndSig();
					mas->method = operation;
					mas->signature = sig;
					JList* list = dynamic_cast<JList*>(parent->ops->get(operationName));
					if(list == null)
						list = JCollections::singletonList(mas);
					else{
						if(list->size() == 1)
							list = JUtil::newList(list);
						list->add(mas);
					}
					parent->ops->put(operationName, dynamic_cast<JObject*>(list));
				}

				JPerInterface::InitMaps::~InitMaps(){
				}


			//----------
			//	MethodAndSig
			//----------
				JPerInterface::MethodAndSig::MethodAndSig():JObject(MethodAndSig::getClazz()){
				}

				JPerInterface::MethodAndSig::~MethodAndSig(){
				}

			//------------
			//	Private
			//------------

				JString* JPerInterface::sigString(JPrimitiveObjectArray* signature){

					JStringBuilder* b = new JStringBuilder(new JString("("));
					if(signature != null){
						for(jint i = 0; i < signature->size(); i++){
							JString* s = dynamic_cast<JString*>(signature->get(i));
							if(b->length() > 1)
								b->append(", ");
							b->append(s);
						}
					}
					return b->append(new JString(")"))->toString();
				}


			//----------
			//	Protected
			//----------
				JPerInterface::JPerInterface(JClass* mbeanInterface, JMBeanIntrospector* introspector, JMBeanAnalyzer* analyzer)
				:JObject(JPerInterface::getClazz()){
					this->getters = JUtil::newMap();
					this->setters = JUtil::newMap();
					this->ops = JUtil::newMap();

					this->mbeanInterface = mbeanInterface;
					this->introspector = introspector;
					analyzer->visit(new InitMaps(this));
				}

				JClass* JPerInterface::getMBeanInterface(){
					return mbeanInterface;
				}


				JObject* JPerInterface::invoke(JObject* resource, JString* operation, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature, JObject* cookie){
					JList* list = dynamic_cast<JList*>(ops->get(operation));
					if(list == null){
						JString* msg = (new JString("No such operation: "))->concat(operation);
						throw new JException(msg);
					}
					if(signature == null)
						signature = new JPrimitiveObjectArray(JString::getClazz(), 0);

					MethodAndSig* found = null;
					JIterator* it = list->iterator();
					while(it->hasNext()){
						MethodAndSig* mas = dynamic_cast<MethodAndSig*>(it->next());
						if(JArrays::equals(mas->signature, signature)){
							found = mas;
							break;
						}
					}
					if(found == null){
						JString* badSig = sigString(signature);
						JString* msg;
						if(list->size() == 1){
							msg = (new JString("Signature mismatch for operation"))->concat(operation);
							msg->concat(new JString(": "))->concat(badSig)->concat(new JString(" should be "));
							msg->concat(dynamic_cast<MethodAndSig*>(list->get(0))->signature->toString());
						}else{
							msg = (new JString("Operation "))->concat(operation)->concat(new JString(" exists but not with this signature: "))->concat(badSig);
						}
						throw new JException(msg);
					}

					return introspector->invokeM(found->method, resource, params, cookie);
				}

				JObject* JPerInterface::getAttribute(JObject* resource, JString* attribute, JObject* cookie){
					JObject* cm = getters->get(attribute);
					if(cm == null){
						JString* msg;
						if(setters->containsKey(attribute))
							msg = (new JString("Write-only attribute: "))->concat(attribute);
						else
							msg = (new JString("No such attribute: "))->concat(attribute);
						throw new JException(msg);
					}
					return introspector->invokeM(cm, resource, null, cookie);
				}

				void JPerInterface::setAttribute(JObject* resource, JString* attribute, JObject* value, JObject* cookie){
					JObject* cm = setters->get(attribute);

					if(cm == null){
						JString* msg;
						if(getters->containsKey(attribute))
							msg = (new JString("Read-only attribute: "))->concat(attribute);
						else
							msg = ( new JString("No such attribute: "))->concat(attribute);
						throw new JException(msg);
					}


					introspector->invokeSetter(attribute, cm, resource, value, cookie);
				}

				JPerInterface::~JPerInterface(){
				}
			}
		}
	}
}
