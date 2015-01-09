#include "jcpp/util/JAbstractCollection.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/reflect/JArray.h"

namespace jcpp{
    namespace util{
        class JAbstractCollectionClass : public jcpp::lang::JClass{
        public:
            JAbstractCollectionClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.AbstractCollection");
                this->name=new JString("java.util.AbstractCollection");
                this->simpleName=new JString("AbstractCollection");
            }

            virtual void initialize(){
                addInterface(JCollection::getClazz());
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JAbstractCollection::getClazz(){
            if (clazz==null){
                clazz=new JAbstractCollectionClass();
            }
            return clazz;
        }

        JAbstractCollection::JAbstractCollection(jcpp::lang::JClass* _class):JObject(_class){
        }

        jbool JAbstractCollection::isEmpty(){
            return size()==0;
        }

        jbool JAbstractCollection::contains(JObject* o){
            JIterator* e = iterator();
            if (o==null) {
                while (e->hasNext()){
                    if (e->next()==null){
                        return true;
                    }
                }
            } else {
                while (e->hasNext())
                if (o->equals(e->next())){
                    return true;
                }
            }
            return false;
        }

        JPrimitiveObjectArray* JAbstractCollection::toArray(){
            JPrimitiveObjectArray* r=new JPrimitiveObjectArray(JObject::getClazz(),size());
            JIterator* it = iterator();
            for (jint i = 0; i < r->size(); i++) {
                it->hasNext();
                JObject* o=it->next();
                r->set(i,o);
            }
            return r;
        }

        JPrimitiveObjectArray* JAbstractCollection::toArray(JPrimitiveObjectArray* a){
            JPrimitiveObjectArray* result=null;
            if (a->size()>=size()){
                result=a;
            }else{
                result=dynamic_cast<JPrimitiveObjectArray*>(JArray::newInstance(a->getComponentType(),size()));
            }

            JIterator* it = iterator();
            for (jint i = 0; i < result->size(); i++) {
                it->hasNext();
                JObject* o=it->next();
                result->set(i,o);
            }
            return result;
        }

        jbool JAbstractCollection::add(JObject*){
            throw new JUnsupportedOperationException();
        }

        jbool JAbstractCollection::remove(JObject* o) {
            JIterator* e = iterator();
            if (o==null) {
                while (e->hasNext()) {
                    if (e->next()==null) {
                        e->remove();
                        return true;
                    }
                }
            } else {
                while (e->hasNext()) {
                    if (o->equals(e->next())) {
                        e->remove();
                        return true;
                    }
                }
            }
            return false;
        }

        jbool JAbstractCollection::containsAll(JCollection* c){
            JIterator* e = c->iterator();
            while (e->hasNext()){
                if (!contains(e->next())){
                    return false;
                }
            }
            return true;
        }

        jbool JAbstractCollection::addAll(JCollection* c){
            jbool modified = false;
            JIterator* e = c->iterator();
            while (e->hasNext()) {
                if (add(e->next())){
                    modified = true;
                }
            }
            return modified;
        }

        jbool JAbstractCollection::removeAll(JCollection* c){
            jbool modified = false;
            JIterator* e = iterator();
            while (e->hasNext()) {
                if (c->contains(e->next())) {
                    e->remove();
                    modified = true;
                }
            }
            return modified;
        }

        jbool JAbstractCollection::retainAll(JCollection* c){
            jbool modified = false;
            JIterator* e = iterator();
            while (e->hasNext()) {
                if (!c->contains(e->next())) {
                    e->remove();
                    modified = true;
                }
            }
            return modified;
        }

        void JAbstractCollection::clear(){
            JIterator* e = iterator();
            while (e->hasNext()) {
                e->next();
                e->remove();
            }
        }

        JString* JAbstractCollection::toString(){
            JIterator* i = iterator();
            if (! i->hasNext()){
                return new JString("[]");
            }

            JStringBuilder* builder=new JStringBuilder();
            builder->append("[");
            for (;;) {
                JObject* o= i->next();
                builder->append((o == this ? new JString("(this Collection)") : o->toString()));
                if (! i->hasNext()){
                    builder->append("]");
                    return builder->toString();
                }
                builder->append(", ");
            }
            return builder->toString();
        }

        JAbstractCollection::~JAbstractCollection(){
        }
    }
}
