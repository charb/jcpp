#include "jcpp/util/JAbstractMap.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JAbstractSet.h"
#include "jcpp/lang/JClassCastException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace util{
        class JAbstractMapClass : public jcpp::lang::JClass{
        public:
            JAbstractMapClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.AbstractMap");
                this->name=new JString("java.util.AbstractMap");
                this->simpleName=new JString("AbstractMap");
            }

            virtual void initialize(){
                addInterface(JMap::getClazz());
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }

            virtual void fillDeclaredClasses();
        };

        static jcpp::lang::JClass* clazz = null;

        jcpp::lang::JClass* JAbstractMap::getClazz(){
            if (clazz==null){
                clazz=new JAbstractMapClass();
            }
            return clazz;
        }

        static jcpp::lang::JClass* simpleEntryClazz = null;

        jcpp::lang::JClass* JAbstractMap::JSimpleEntry::getClazz(){
            if (simpleEntryClazz==null){
                simpleEntryClazz=new JSimpleEntryClass();
            }
            return simpleEntryClazz;
        }

        static jcpp::lang::JClass* simpleImmutableEntryClazz = null;

        jcpp::lang::JClass* JAbstractMap::JSimpleImmutableEntry::getClazz(){
            if (simpleImmutableEntryClazz==null){
                simpleImmutableEntryClazz=new JSimpleImmutableEntryClass();
            }
            return simpleImmutableEntryClazz;
        }

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

        static jcpp::lang::JClass* abstractSetIteratorImplClazz;
        class JAbstractSetIteratorImpl : public JIterator, public JObject{
        protected:
            class JAbstractSetIteratorImplClass : public jcpp::lang::JClass{
            public:
                JAbstractSetIteratorImplClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.util.AbstractMap$AbstractSet$Iterator");
                    this->name=new JString("java.util.AbstractMap$AbstractSet$Iterator");
                    this->simpleName=new JString("AbstractMap$AbstractSet$Iterator");
                }

                virtual void initialize(){
                    addInterface(JIterator::getClazz());
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JObject::getClazz();
                }

                virtual jcpp::lang::JClass* getDeclaringClass();
            };

            JIterator* i;
        public:
            static jcpp::lang::JClass* getClazz(){
                if (abstractSetIteratorImplClazz==null){
                    abstractSetIteratorImplClazz=new JAbstractSetIteratorImplClass();
                }
                return abstractSetIteratorImplClazz;
            }

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

        static jcpp::lang::JClass* abstractSetImplClazz;
        class JAbstractSetImpl : public JAbstractSet{
        protected:
            JAbstractMap* map;
            class JAbstractSetImplClass : public jcpp::lang::JClass{
            public:
                JAbstractSetImplClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.util.AbstractMap$AbstractSet");
                    this->name=new JString("java.util.AbstractMap$AbstractSet");
                    this->simpleName=new JString("AbstractMap$AbstractSet");
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JAbstractSet::getClazz();
                }

                virtual jcpp::lang::JClass* getDeclaringClass(){
                    return JAbstractMap::getClazz();
                }

                virtual void fillDeclaredClasses(){
                    addDeclaredClass(JAbstractSetIteratorImpl::getClazz());
                }
            };
        public:

            static jcpp::lang::JClass* getClazz(){
                if (abstractSetImplClazz==null){
                    abstractSetImplClazz=new JAbstractSetImplClass();
                }
                return abstractSetImplClazz;
            }

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

        jcpp::lang::JClass* JAbstractSetIteratorImpl::JAbstractSetIteratorImplClass::getDeclaringClass(){
            return JAbstractSetImpl::getClazz();
        }

        JSet* JAbstractMap::keySet(){
            return new JAbstractSetImpl(this);
        }

        static jcpp::lang::JClass* abstractCollectionIteratorImplClazz;
        class JAbstractCollectionIteratorImpl : public JIterator, public JObject{
        protected:
            class JAbstractCollectionIteratorImplClass : public jcpp::lang::JClass{
            public:
                JAbstractCollectionIteratorImplClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.util.AbstractMap$AbstractCollection$Iterator");
                    this->name=new JString("java.util.AbstractMap$AbstractCollection$Iterator");
                    this->simpleName=new JString("AbstractMap$AbstractCollection$Iterator");
                }

                virtual void initialize(){
                    addInterface(JIterator::getClazz());
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JObject::getClazz();
                }

                virtual jcpp::lang::JClass* getDeclaringClass();
            };

            JIterator* i;
        public:
            static jcpp::lang::JClass* getClazz(){
                if (abstractCollectionIteratorImplClazz==null){
                    abstractCollectionIteratorImplClazz=new JAbstractCollectionIteratorImplClass();
                }
                return abstractCollectionIteratorImplClazz;
            }

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

        static jcpp::lang::JClass* abstractCollectionImplClazz;
        class JAbstractCollectionImpl : public JAbstractCollection{
        protected:
            JAbstractMap* map;
            class JAbstractCollectionImplClass : public jcpp::lang::JClass{
            public:
                JAbstractCollectionImplClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.util.AbstractMap$AbstractCollection");
                    this->name=new JString("java.util.AbstractMap$AbstractCollection");
                    this->simpleName=new JString("AbstractMap$AbstractCollection");
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JAbstractCollection::getClazz();
                }

                virtual jcpp::lang::JClass* getDeclaringClass(){
                    return JAbstractMap::getClazz();
                }

                virtual void fillDeclaredClasses(){
                    addDeclaredClass(JAbstractCollectionIteratorImpl::getClazz());
                }
            };
        public:

            static jcpp::lang::JClass* getClazz(){
                if (abstractCollectionImplClazz==null){
                    abstractCollectionImplClazz=new JAbstractCollectionImplClass();
                }
                return abstractCollectionImplClazz;
            }

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

        jcpp::lang::JClass* JAbstractCollectionIteratorImpl::JAbstractCollectionIteratorImplClass::getDeclaringClass(){
            return JAbstractCollectionImpl::getClazz();
        }

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

        void JAbstractMapClass::fillDeclaredClasses(){
            addDeclaredClass(JAbstractMap::JSimpleEntry::getClazz());
            addDeclaredClass(JAbstractMap::JSimpleImmutableEntry::getClazz());
            addDeclaredClass(JAbstractCollectionImpl::getClazz());
            addDeclaredClass(JAbstractSetImpl::getClazz());
        }

        JAbstractMap::~JAbstractMap(){
        }
    }
}
