#include "jcpp/lang/jmx/internal/JRepository.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/jmx/JObjectName.h"
#include "jcpp/lang/jmx/internal/JNamedObject.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//------------
			//	Private
			//------------
				void JRepository::addNewDomainMoi(JDynamicMBean* object, JString* dom, JObjectName* name){
					JMap* moiTb = new JHashMap();
					moiTb->put(name->getCanonicalKeyPropertyListString(), new JNamedObject(object));
					domainTb->put(dom, dynamic_cast<JObject*>(moiTb));
					nbElements++;
				}

				JNamedObject* JRepository::retrieveNamedObject(JObjectName* name){
					JString* dom = name->getDomain();
					if(dom->length() == 0){
						dom = domain;
					}
					JMap* moiTb = dynamic_cast<JMap*>(domainTb->get(dom));
					if(moiTb == null){
						return null;
					}
					return dynamic_cast<JNamedObject*>(moiTb->get(name->getCanonicalKeyPropertyListString()));
				}

			//-------------
			//	Public
			//-------------
				JRepository::JRepository(JString* domain, jbool fairLock):JObject(JRepository::getClazz()){

					nbElements = 0;
					lock = new JString();	//TODO should be changed to readWriteLock
					domainTb = new JHashMap(5, 0.75f);

					if(domain != null && domain->length() != 0)
						this->domain = domain;
					else{
						this->domain = new JString("default domain");
					}

					domainTb->put(this->domain,new JHashMap());
				}

				JPrimitiveObjectArray* JRepository::getDomains(){
					synchronized(lock,
						JList* result;
						try{
							result = new JArrayList(domainTb->size());
							JIterator* it = domainTb->entrySet()->iterator();
							while(it->hasNext()){
								JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(it->next());
								JMap* t = dynamic_cast<JMap*>(entry->getValue());
								if(t != null && t->size() != 0)
									result->add(entry->getKey());
							}
						} catch (JException* e){
						}
						return result->toArray(new JPrimitiveObjectArray(JString::getClazz(), result->size()));
					)

				}

				void JRepository::addMBean(JDynamicMBean* object, JObjectName* name){

					JString* dom = name->getDomain();

					if(dom->length() == 0){
						try{
							name = new JObjectName(domain->concat(name->toString()));
						} catch(JException* e){
						}
					}


					if(dom == domain){
						dom = domain;
					}


					synchronized(lock,
					{
						try{

							JMap* moiTb = dynamic_cast<JMap*>(domainTb->get(dom));
							if(moiTb == null){
								addNewDomainMoi(object, dom, name);
								return;
							}

							JString* cstr = name->getCanonicalKeyPropertyListString();
							JNamedObject* elmt = dynamic_cast<JNamedObject*>(moiTb->get(cstr));
							if(elmt != null){
								throw new JException(name->toString());
							}else{
								nbElements++;
								moiTb->put(cstr, new JNamedObject(object));
							}
						}catch (JException* e){
						}

					})
				}

				jbool JRepository::contains(JObjectName* name){
					synchronized(lock,
						try{
							return retrieveNamedObject(name) != null;
						} catch(JException* e){
							return false;
						}
					)
				}

				JDynamicMBean* JRepository::retrieve(JObjectName* name){
					synchronized(lock,
						try{
							JNamedObject* no = retrieveNamedObject(name);
							if(no == null)
								return null;
							else
								return no->getObject();
						} catch (JException* e){
							return null;
						}
					)
				}

				JInteger* JRepository::getCount(){
					return new JInteger(nbElements);
				}

				JString* JRepository::getDefaultDomain(){
					return domain;
				}


				JRepository::~JRepository(){
				}
			}
		}
	}
}
