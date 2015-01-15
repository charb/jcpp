#include "jcpp/util/JAbstractSet.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JListIterator.h"
#include "jcpp/lang/JClassCastException.h"
#include "jcpp/lang/JNullPointerException.h"

namespace jcpp{
    namespace util{

        JAbstractSet::JAbstractSet(jcpp::lang::JClass* _class):JAbstractCollection(_class){
        }

        JPrimitiveObjectArray* JAbstractSet::toArray(){
            return JAbstractCollection::toArray();
        }

        JPrimitiveObjectArray* JAbstractSet::toArray(JPrimitiveObjectArray* a){
            return JAbstractCollection::toArray(a);
        }

        jbool JAbstractSet::isEmpty(){
            return JAbstractCollection::isEmpty();
        }

        jbool JAbstractSet::contains(JObject* o) {
        	return JAbstractCollection::contains(o);
        }

        jbool JAbstractSet::add(JObject* e){
            return JAbstractCollection::add(e);
        }

        jbool JAbstractSet::remove(JObject* o){
            return JAbstractCollection::remove(o);
        }

        jbool JAbstractSet::containsAll(JCollection* c){
            return JAbstractCollection::containsAll(c);
        }

        jbool JAbstractSet::addAll(JCollection* c){
            return JAbstractCollection::addAll(c);
        }

        jbool JAbstractSet::retainAll(JCollection* c){
            return JAbstractCollection::retainAll(c);
        }

        jbool JAbstractSet::removeAll(JCollection* c){
            jbool modified = false;
            if (size() > c->size()) {
                JIterator* i = c->iterator();
                for (; i->hasNext(); ){
                    modified |= remove(i->next());
                }
            } else {
                JIterator* i = iterator();
                for (; i->hasNext(); ) {
                    if (c->contains(i->next())) {
                        i->remove();
                        modified = true;
                    }
                }
            }
            return modified;
        }

        void JAbstractSet::clear() {
        	JAbstractCollection::clear();
        }

        jbool JAbstractSet::equals(JObject* o){
            if (o == this){
                return true;
            }
            if ((o == null) || !JSet::getClazz()->isAssignableFrom(o->getClass())){
                return false;
            }
            JSet* c = dynamic_cast<JSet*>(o);
            if (c->size() != size()){
                return false;
            }
            try {
                return containsAll(c);
            } catch (JClassCastException* unused)   {
                return false;
            } catch (JNullPointerException* unused) {
                return false;
            }
        }

        jint JAbstractSet::hashCode(){
            jint h = 0;
            JIterator* i = iterator();
            while (i->hasNext()) {
                JObject* obj = i->next();
                if (obj != null){
                    h += obj->hashCode();
                }
            }
            return h;
        }

        JAbstractSet::~JAbstractSet(){
        }
    }
}

