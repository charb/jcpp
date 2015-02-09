#include "jcpp/util/JAbstractSequentialList.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JListIterator.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

        
        JAbstractSequentialList::JAbstractSequentialList(jcpp::lang::JClass* _class):JAbstractList(_class){
        }

            
        JObject* JAbstractSequentialList::get(jint index){
            try {
                return listIterator(index)->next();
            } catch (JNoSuchElementException* exc) {
                throw new JIndexOutOfBoundsException();
            }
        }

        JObject* JAbstractSequentialList::set(jint index,JObject* element){
            try {
                JListIterator* e = listIterator(index);
                JObject* oldVal = e->next();
                e->set(element);
                return oldVal;
            } catch (JNoSuchElementException* exc) {
                throw new JIndexOutOfBoundsException();
            }
        }

        void JAbstractSequentialList::add(jint index, JObject* element){
            try {
                listIterator(index)->add(element);
            } catch (JNoSuchElementException* exc) {
                throw new JIndexOutOfBoundsException();
            }
        }

        JObject* JAbstractSequentialList::remove(jint index){
            try {
                JListIterator* e = listIterator(index);
                JObject* outCast = e->next();
                e->remove();
                return outCast;
            } catch (JNoSuchElementException* exc) {
                throw new JIndexOutOfBoundsException();
            }
        }

        jbool JAbstractSequentialList::addAll(jint index, JCollection* c){
            try {
                jbool modified = false;
                JListIterator* e1 = listIterator(index);
                JIterator* e2 = c->iterator();
                while (e2->hasNext()) {
                    e1->add(dynamic_cast<JObject*>(e2->next()));
                    modified = true;
                }
                return modified;
            } catch (JNoSuchElementException* exc) {
                throw new JIndexOutOfBoundsException();
            }
        }

        JIterator* JAbstractSequentialList::iterator(){
            return JAbstractList::listIterator();
        }

        JAbstractSequentialList::~JAbstractSequentialList(){
        }
    }
}
