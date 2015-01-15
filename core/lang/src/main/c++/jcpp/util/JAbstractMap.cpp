#include "jcpp/util/JAbstractMap.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JAbstractSet.h"
#include "jcpp/lang/JClassCastException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace util{

        JAbstractMap::JAbstractMap(jcpp::lang::JClass* _class):JObject(_class){
        }

        jint JAbstractMap::size(){
            return entrySet()->size();
        }

        jbool JAbstractMap::isEmpty(){
            return size()==0;
        }

        jbool JAbstractMap::containsValue(JObject* value){
            JIterator* i = entrySet()->iterator();
            if (value==null) {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (e->getValue()==null){
                        return true;
                    }
                }
            } else {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (value->equals(e->getValue())){
                        return true;
                    }
                }
            }
            return false;
        }

        jbool JAbstractMap::containsKey(JObject* key){
            JIterator* i = entrySet()->iterator();
            if (key==null) {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (e->getKey()==null){
                        return true;
                    }
                }
            } else {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (key->equals(e->getKey())){
                        return true;
                    }
                }
            }
            return false;
        }

        JObject* JAbstractMap::get(JObject* key){
            JIterator* i = entrySet()->iterator();
            if (key==null) {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (e->getKey()==null){
                        JObject* o=e->getValue();
                        return o;
                    }
                }
            } else {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (key->equals(e->getKey())){
                        JObject* o=e->getValue();
                        return o;
                    }
                }
            }
            return null;
        }

        JObject* JAbstractMap::put(JObject*, JObject*){
            throw new JUnsupportedOperationException();
        }

        JObject* JAbstractMap::remove(JObject* key){
            JIterator* i = entrySet()->iterator();
            JEntry* correctEntry = null;
            if (key==null) {
                while (correctEntry==null && i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (e->getKey()==null){
                        correctEntry = e;
                    }
                }
            } else {
                while (correctEntry==null && i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    if (key->equals(e->getKey())){
                        correctEntry = e;
                    }
                }
            }
            JObject* oldValue = null;
            if (correctEntry !=null) {
                oldValue = correctEntry->getValue();
                i->remove();
            }
            return oldValue;
        }

        void JAbstractMap::putAll(JMap* m){
            JIterator* i=m->entrySet()->iterator();
            while (i->hasNext()){
                JEntry* e = dynamic_cast<JEntry*>(i->next());
                put(e->getKey(), e->getValue());
            }
        }

        void JAbstractMap::clear(){
            entrySet()->clear();
        }

        // @Class(canonicalName="java.util.AbstractMap$AbstractSet$Iterator", simpleName="AbstractMap$AbstractSet$Iterator");
        class JAbstractSetIteratorImpl : public JIterator, public JObject{
        protected:
            JIterator* i;
        public:
            static jcpp::lang::JClass* getClazz();

            JAbstractSetIteratorImpl(JAbstractMap* map):JObject(getClazz()){
                i=map->entrySet()->iterator();
            }

            virtual jbool hasNext() {
                return i->hasNext();
            }

            virtual JObject* next() {
                JMap::JEntry* e=dynamic_cast<JMap::JEntry*>(i->next());
                return e->getKey();
            }

            virtual void remove() {
                i->remove();
            }

            ~JAbstractSetIteratorImpl(){
            }
        };

        // @Class(canonicalName="java.util.AbstractMap$AbstractSet", simpleName="AbstractMap$AbstractSet");
        class JAbstractSetImpl : public JAbstractSet{
        protected:
            JAbstractMap* map;
        public:

            static jcpp::lang::JClass* getClazz();

            JAbstractSetImpl(JAbstractMap* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            virtual JIterator* iterator() {
                return new JAbstractSetIteratorImpl(map);
            }

            virtual jint size() {
                return map->size();
            }

            virtual jbool isEmpty() {
                return map->isEmpty();
            }

            virtual void clear() {
                map->clear();
            }

            virtual jbool contains(JObject* k) {
                return map->containsKey(k);
            }
        };

        JSet* JAbstractMap::keySet(){
            return new JAbstractSetImpl(this);
        }

        // @Class(canonicalName="java.util.AbstractMap$AbstractCollection$Iterator", simpleName="AbstractMap$AbstractCollection$Iterator");
        class JAbstractCollectionIteratorImpl : public JIterator, public JObject{
        protected:
            JIterator* i;
        public:
            static jcpp::lang::JClass* getClazz();

            JAbstractCollectionIteratorImpl(JAbstractMap* map):JObject(getClazz()){
                i=map->entrySet()->iterator();
            }

            virtual jbool hasNext() {
                return i->hasNext();
            }

            virtual JObject* next() {
                JMap::JEntry* e=dynamic_cast<JMap::JEntry*>(i->next());
                return e->getKey();
            }

            virtual void remove() {
                i->remove();
            }

            ~JAbstractCollectionIteratorImpl(){
            }
        };

        // @Class(canonicalName="java.util.AbstractMap$AbstractCollection", simpleName="AbstractMap$AbstractCollection");
        class JAbstractCollectionImpl : public JAbstractCollection{
        protected:
            JAbstractMap* map;
        public:

            static jcpp::lang::JClass* getClazz();

            JAbstractCollectionImpl(JAbstractMap* map):JAbstractCollection(getClazz()){
                this->map=map;
            }

            virtual JIterator* iterator() {
                return new JAbstractCollectionIteratorImpl(map);
            }

            virtual jint size() {
                return map->size();
            }

            virtual jbool isEmpty() {
                return map->isEmpty();
            }

            virtual void clear() {
                map->clear();
            }

            virtual jbool contains(JObject* v) {
                return map->containsValue(v);
            }

            virtual jbool equals(JObject *o){
                return JObject::equals(o);
            }

            virtual jint hashCode(){
                return JObject::hashCode();
            }
        };

        JCollection* JAbstractMap::values(){
            return new JAbstractCollectionImpl(this);
        }

        jbool JAbstractMap::equals(JObject* o){
            if (o == this){
                return true;
            }

            if ((o == null) || !JMap::getClazz()->isAssignableFrom(o->getClass())){
                 return false;
            }
            JMap* m=dynamic_cast<JMap*>(o);
            if (m->size() != size()){
                 return false;
            }
            JIterator* i = entrySet()->iterator();
            try {
                while (i->hasNext()) {
                    JEntry* e = dynamic_cast<JEntry*>(i->next());
                    JObject* key = e->getKey();
                    JObject* value = e->getValue();
                    if (value == null) {
                        if (!(m->get(key)==null && m->containsKey(key))){
                            return false;
                        }
                    } else {
                        JObject* v2=m->get(key);
                        if (v2==null || !value->equals(v2)){
                            return false;
                        }
                    }
                }
            } catch (JClassCastException* unused) {
                return false;
            } catch (JNullPointerException* unused) {
                return false;
            }
            return true;
        }

        jint JAbstractMap::hashCode(){
            jint h = 0;
            JIterator* i = entrySet()->iterator();
            while (i->hasNext()){
                h += i->next()->hashCode();
            }
            return h;
        }

        JString* JAbstractMap::toString(){
            JIterator* i = entrySet()->iterator();
            if (!i->hasNext()){
                return new JString("{}");
            }

            JStringBuilder* builder=new JStringBuilder();
            builder->append("{");
            for (;;) {
                JEntry* e = dynamic_cast<JEntry*>(i->next());
                JObject* key = e->getKey();
                JObject* value = e->getValue();
                builder->append((key == this ? new JString("(this Map)") : key->toString()));
                builder->append("=");
                builder->append((value == this ? new JString("(this Map)") : value->toString()));
                if (!i->hasNext()){
                    builder->append("}");
                    return builder->toString();
                }
                builder->append(", ");
            }
            return builder->toString();
        }

        JAbstractMap::~JAbstractMap(){
        }
    }
}
