#include "jcpp/lang/jmx/internal/JMBeanAnalyzer.h"
#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/jmx/internal/JIntrospector.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveVoid.h"
#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/lang/jmx/internal/JMBeanIntrospector.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			//-------------
			//	MBeanVisitor
			//-------------

			JMBeanAnalyzer::JMBeanVisitor::~JMBeanVisitor(){
			}

			//------------
			//	JMethodOrder
			//------------
				JMBeanAnalyzer::JMethodOrder* JMBeanAnalyzer::JMethodOrder::instance = new JMethodOrder();

				JMBeanAnalyzer::JMethodOrder::JMethodOrder():JObject(JMethodOrder::getClazz()){
				}


				jint JMBeanAnalyzer::JMethodOrder::compare(JObject* a, JObject* b){
					JMethod* a_m = dynamic_cast<JMethod*>(a);
					JMethod* b_m = dynamic_cast<JMethod*>(b);

					jint cmp = a_m->getName()->compareTo(b_m->getName());
					if(cmp != 0)
						return cmp;

					JPrimitiveObjectArray* aparams = a_m->getParameterTypes()->toArray();
					JPrimitiveObjectArray* bparams = b_m->getParameterTypes()->toArray();
					if(aparams->size() != bparams->size())
						return aparams->size() - bparams->size();
					if(!JArrays::equals(aparams, bparams)){
						return JArrays::toStringStatic(aparams)->compareTo(JArrays::toStringStatic(bparams));
					}
					JClass* aret = a_m->getReturnType();
					JClass* bret = b_m->getReturnType();
					if(aret == bret)
						return 0;
					if(aret->isAssignableFrom(bret))
						return -1;
					return 1;
				}

				JMBeanAnalyzer::JMethodOrder::~JMethodOrder(){
				}

			//-----------
			//	JAttrMethods
			//-----------

				JMBeanAnalyzer::JAttrMethods::JAttrMethods():JObject(JAttrMethods::getClazz()){
				}
				JMBeanAnalyzer::JAttrMethods::~JAttrMethods(){
				}

			//-------------
			// Private
			//-------------
				JMBeanAnalyzer::JMBeanAnalyzer(JClass* mbeanInterface, JMBeanIntrospector* introspector):JObject(JMBeanAnalyzer::getClazz()){
					opMap = JUtil::newInsertionOrderMap();
					attrMap = JUtil::newInsertionOrderMap();

					if(!mbeanInterface->isInterface()){
						throw new JException((new JString("Not an interface: "))->concat(mbeanInterface->getName()));
					}
					try{
						initMaps(mbeanInterface, introspector);
					} catch (JException* x){
						throw JIntrospector::throwException(mbeanInterface, x);
					}
				}

				void JMBeanAnalyzer::initMaps(JClass* mbeanInterface, JMBeanIntrospector*introspector){
					JPrimitiveObjectArray* methodArray = mbeanInterface->getMethods()->toArray();

					JList* methods = eliminateCovariantMethods(methodArray);

					JIterator* it = methods->iterator();
					while(it->hasNext()){
						JMethod* m = dynamic_cast<JMethod*>(it->next());

						JString* name = m->getName();

						JObject* cm = introspector->mFrom(m);

						JString* attrName = new JString("");

						if(name->startsWith(new JString("get")))
							attrName = name->substring(3);
						else if(name->startsWith(new JString("is")) && m->getReturnType() == JPrimitiveBoolean::getClazz())
							attrName = name->substring(2);

						if(attrName->length() != 0 && m->getParameterTypes()->size() == 0 && m->getReturnType() != JPrimitiveVoid::getClazz()){
							JAttrMethods* am = dynamic_cast<JAttrMethods*>(attrMap->get(attrName));
							if(am == null)
							am = new JAttrMethods();
							else{
								if(am->getter != null){
									JString* msg = ((new JString("Attribute "))->concat(attrName))->concat(new JString(" has more than one getter"));
									throw new JException(msg);
								}
							}
							am->getter = cm;
							attrMap->put(attrName, am);
						}else if(name->startsWith(new JString("set")) && name->length() > 3 && m->getParameterTypes()->size() == 1 && m->getReturnType() == JPrimitiveVoid::getClazz()){
							attrName = name->substring(3);
							JAttrMethods* am = dynamic_cast<JAttrMethods*>(attrMap->get(attrName));
							if(am == null)
								am = new JAttrMethods();
							else if(am->setter != null){
								JString* msg = ((new JString("Attribute "))->concat(attrName))->concat(new JString(" has more than one setter"));
								throw new JException(msg);
							}
							am->setter = cm;
							attrMap->put(attrName, am);
						}else{
							JList* cms = dynamic_cast<JList*>(opMap->get(name));
							if(cms == null)
								cms = JUtil::newList();
							cms->add(cm);
							opMap->put(name, dynamic_cast<JObject*>(cms));
						}
					}
					JIterator* mapIterator = attrMap->entrySet()->iterator();
					while(mapIterator->hasNext()){
						JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(mapIterator->next());
						JAttrMethods* am = dynamic_cast<JAttrMethods*>(entry->getValue());
						if(!introspector->consistent(am->getter, am->setter)){
							JString* msg = (new JString("Getter and setter for "))->concat(dynamic_cast<JString*>(entry->getKey()));
							msg->concat(new JString(" have inconsistent types"));
							throw new JException(msg);
						}
					}
				}

			//-------------
			//	Protected
			//-------------
				JList* JMBeanAnalyzer::eliminateCovariantMethods(JPrimitiveObjectArray* methodArray){
					jint len = methodArray->size();
					JPrimitiveObjectArray* sorted = methodArray->clone();
					JArrays::sort(sorted, JMethodOrder::instance);
					JSet* overridden = JUtil::newSet();
					for(jint i = 1; i < len; i++){
						JMethod* m0 = dynamic_cast<JMethod*>(sorted->get(i - 1));
						JMethod* m1 = dynamic_cast<JMethod*>(sorted->get(i));

						if(!m0->getName()->equals(m1->getName()))
							continue;

						if(JArrays::equals(m0->getParameterTypes()->toArray(), m1->getParameterTypes()->toArray())){
							overridden->add(m0);
						}
					}

					JList* methods = JUtil::newList(JArrays::asList(methodArray));
					methods->removeAll(overridden);
					return methods;

				}

				JMBeanAnalyzer* JMBeanAnalyzer::analyzer(JClass* mbeanInterface, JMBeanIntrospector* introspector){
					return new JMBeanAnalyzer(mbeanInterface, introspector);
				}

				void JMBeanAnalyzer::visit(JMBeanVisitor* visitor){
					JIterator* it = attrMap->entrySet()->iterator();
					while(it->hasNext()){
						JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(it->next());
						JString* name = dynamic_cast<JString*>(entry->getKey());
						JAttrMethods* am = dynamic_cast<JAttrMethods*>(entry->getValue());
						visitor->visitAttribute(name, am->getter, am->setter);
					}

					it = opMap->entrySet()->iterator();
					while(it->hasNext()){
						JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(it->next());
						JList* v = dynamic_cast<JList*>(entry->getValue());
						JIterator* vit = v->iterator();
						while(vit->hasNext()){
							JObject* m = vit->next();
							visitor->visitOperation(dynamic_cast<JString*>(entry->getKey()), m);
						}
					}
				}
			//-----------
			//	Public
			//-----------

				JMBeanAnalyzer::~JMBeanAnalyzer(){
				}
			}
		}
	}
}
