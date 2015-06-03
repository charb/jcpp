#include "jcpp/util/JCollections.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/util/JRandomAccess.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JField.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;

namespace jcpp{
    namespace util{
    	class JUnmodifiableCollectionClass;
    	class JUnmodifiableListClass;

    	// @Class(canonicalName="java.util.Collections$UnmodifiableCollection$Iterator", simpleName="Collections$UnmodifiableCollection$Iterator");
        class JUnmodifiableCollectionIterator : public JObject, public JIterator{
        protected:
            JCollection* c;
            JIterator* i;

        public:
            JUnmodifiableCollectionIterator(JCollection* c):JObject(getClazz()){
                this->c=c;
                this->i=c->iterator();
            }   

            static jcpp::lang::JClass* getClazz();

            virtual jbool hasNext() {
                return i->hasNext();
            }
            
            virtual JObject* next(){
                return i->next();
            }
            
            virtual void remove() {
                throw new JUnsupportedOperationException();
            }
        };

        // @Class(canonicalName="java.util.Collections$UnmodifiableCollection", simpleName="Collections$UnmodifiableCollection");
        class JUnmodifiableCollection : public JObject, public JCollection, public JSerializable {
        protected:
            JCollection* c;

            JUnmodifiableCollection(jcpp::lang::JClass* _class,JCollection* c) : JObject(_class) {
                if (c==null){
                    throw new JNullPointerException();
                }
                this->c = c;
            }
            friend class JUnmodifiableCollectionClass;

        public:

            JUnmodifiableCollection() : JObject(getClazz()) {
                this->c = null;
            }

            JUnmodifiableCollection(jcpp::lang::JClass* c) : JObject(c) {
                this->c = null;
            }

            JUnmodifiableCollection(JCollection* c) : JObject(getClazz()) {
                if (c==null){
                    throw new JNullPointerException();
                }
                this->c = c;
            }

            static jcpp::lang::JClass* getClazz();

            virtual jint size(){
                return c->size();
            }
            
            virtual jbool isEmpty(){
                return c->isEmpty();
            }

            virtual jbool contains(JObject* o){
                return c->contains(o);
            }
            
            virtual JPrimitiveObjectArray* toArray(){
                return c->toArray();
            }

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a){
                return c->toArray(a);
            }
            
            virtual JString* toString(){
                if (c!=null){
                    return dynamic_cast<JObject*>(c)->toString();
                }
                return null;
            }

            virtual JIterator* iterator() {
                return new JUnmodifiableCollectionIterator(c);
            }

            virtual jbool add(JObject* e) {
                throw new JUnsupportedOperationException();
            }
            
            virtual jbool remove(JObject* o) {
                throw new JUnsupportedOperationException();
            }

            virtual jbool containsAll(JCollection* coll) {
                return c->containsAll(coll);
            }

            virtual jbool addAll(JCollection* coll) {
                throw new JUnsupportedOperationException();
            }

            virtual jbool removeAll(JCollection* coll) {
                throw new JUnsupportedOperationException();
            }

            virtual jbool retainAll(JCollection* coll) {
                throw new JUnsupportedOperationException();
            }

            virtual void clear() {
                throw new JUnsupportedOperationException();
            }
        };

        JCollection* JCollections::unmodifiableCollection(JCollection* c){
            return new JUnmodifiableCollection(c);
        }

        // @Class(canonicalName="java.util.Collections$UnmodifiableList$ListIterator", simpleName="Collections$UnmodifiableList$ListIterator");
        class JUnmodifiableListIterator : public JObject, public JListIterator{
        protected:
            JList* list;
            JListIterator* i;

        public:
            JUnmodifiableListIterator(JList* list,jint index): JObject(getClazz()){
                this->list=list;
                i=list->listIterator(index);
            }

            static jcpp::lang::JClass* getClazz();

            virtual jbool hasNext(){
                return i->hasNext();
            }
            
            virtual JObject* next(){
                return i->next();
            }
            
            virtual jbool hasPrevious() {
                return i->hasPrevious();
            }

            virtual JObject* previous(){
                return i->previous();
            }
            
            virtual jint nextIndex(){
                return i->nextIndex();
            }
            
            virtual jint previousIndex(){
                return i->previousIndex();
            }

            virtual void remove() {
                throw new JUnsupportedOperationException();
            }
            
            virtual void set(JObject* e) {
                throw new JUnsupportedOperationException();
            }

            virtual void add(JObject* e) {
                throw new JUnsupportedOperationException();
            }
        };

        // @Class(canonicalName="java.util.Collections$UnmodifiableList", simpleName="Collections$UnmodifiableList");
        class JUnmodifiableList : public JUnmodifiableCollection, public JList{
        private:
        	static const jlong serialVersionUID = -283967356065247728LL;

        protected:
            JList* list;

            JUnmodifiableList(jcpp::lang::JClass* c,JList* list) : JUnmodifiableCollection(c,list) {
                this->list = list;
            }

            friend class JUnmodifiableListClass;

        public:
            JUnmodifiableList() : JUnmodifiableCollection(getClazz()) {
                this->list = null;
            }

            JUnmodifiableList(JList* list) : JUnmodifiableCollection(getClazz(),list) {
                this->list = list;
            }

            static jcpp::lang::JClass* getClazz();

            virtual jbool equals(JObject* o) {
                return o == this || list->equals(o);
            }

            virtual jint hashCode(){
                return list->hashCode();
            }

            virtual JObject* get(jint index) {
                return list->get(index);
            }
        
            virtual JObject* set(jint index, JObject* element) {
                throw new JUnsupportedOperationException();
            }
        
            virtual void add(jint index, JObject* element) {
                throw new JUnsupportedOperationException();
            }

            virtual JObject* remove(jint index) {
                throw new JUnsupportedOperationException();
            }
        
            virtual jint indexOf(JObject* o){
                return list->indexOf(o);
            }

            virtual jint lastIndexOf(JObject* o){
                return list->lastIndexOf(o);
            }

            virtual jbool addAll(jint index, JCollection* c) {
                throw new JUnsupportedOperationException();
            }

            virtual JListIterator* listIterator(){
                return listIterator(0);
            }

            virtual JListIterator* listIterator(jint index) {
                return new JUnmodifiableListIterator(list,index);
            }

            virtual JList* subList(jint fromIndex, jint toIndex) {
                return new JUnmodifiableList(list->subList(fromIndex, toIndex));
            }

            virtual JObject* readResolve();

            virtual jbool add(JObject* c) {
                return JUnmodifiableCollection::add(c);
            }

            virtual jbool addAll(JCollection* c) {
                return JUnmodifiableCollection::addAll(c);
            }

            virtual jbool remove(JObject* c) {
                return JUnmodifiableCollection::remove(c);
            }

            virtual void clear() {
                return JUnmodifiableCollection::clear();
            }

            virtual jbool removeAll(JCollection* c) {
                return JUnmodifiableCollection::removeAll(c);
            }

            virtual jbool retainAll(JCollection* c) {
                return JUnmodifiableCollection::retainAll(c);
            }

            virtual jint size(){
                return JUnmodifiableCollection::size();
            }

            virtual jbool isEmpty(){
                return JUnmodifiableCollection::isEmpty();
            }

            virtual jbool contains(JObject* o){
                return JUnmodifiableCollection::contains(o);
            }

            virtual JIterator* iterator(){
                return JUnmodifiableCollection::iterator();
            }

            virtual JPrimitiveObjectArray* toArray(){
                return JUnmodifiableCollection::toArray();
            }

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a){
                return JUnmodifiableCollection::toArray(a);
            }

            virtual jbool containsAll(JCollection* c){
                return JUnmodifiableCollection::containsAll(c);
            }
        };

        // @Class(canonicalName="java.util.Collections$UnmodifiableRandomAccessList", simpleName="Collections$UnmodifiableRandomAccessList");
        class JUnmodifiableRandomAccessList : public JUnmodifiableList, public JRandomAccess{
        private:
        	static const jlong serialVersionUID = -2542308836966382001LL;

        public:
            JUnmodifiableRandomAccessList(JList* list) : JUnmodifiableList(getClazz(),list){
            }

            static jcpp::lang::JClass* getClazz();

            virtual JList* subList(jint fromIndex, jint toIndex) {
                return new JUnmodifiableRandomAccessList(list->subList(fromIndex, toIndex));
            }

            virtual JObject* writeReplace() {
                return new JUnmodifiableList(list);
            }
        };

        JObject* JUnmodifiableList::readResolve() {
            return (dynamic_cast<JObject*>(list)->isInstanceOf(JRandomAccess::getClazz()) ? new JUnmodifiableRandomAccessList(list) : this);
        }

        JList* JCollections::unmodifiableList(JList* list){
            return (dynamic_cast<JObject*>(list)->isInstanceOf(JRandomAccess::getClazz()) ? new JUnmodifiableRandomAccessList(list) : new JUnmodifiableList(list));
        }



        // @Class(canonicalName="java.util.Collections$SynchronizedCollection", simpleName="Collections$SynchronizedCollection");
        class JSynchronizedCollection : public JObject, public JCollection, public JSerializable {
        private:
        	static jcpp::lang::JClass* synchronizedCollectionClazz;
        	static const jlong serialVersionUID = 3053995032091335093LL;
        protected:
            JCollection* c;
            JObject* mutex;

        public:
            static jcpp::lang::JClass* getClazz();

            JSynchronizedCollection(JCollection* c):JObject(getClazz()) {
                if (c==null){
                    throw new JNullPointerException();
                }
                this->c = c;
                mutex = this;
            }

            JSynchronizedCollection(jcpp::lang::JClass* _class,JCollection* c):JObject(_class) {
                if (c==null){
                    throw new JNullPointerException();
                }
                this->c = c;
                mutex = this;
            }

            JSynchronizedCollection(jcpp::lang::JClass* _class,JCollection* c, JObject* mutex):JObject(_class){
                this->c = c;
                this->mutex = mutex;
            }

            JSynchronizedCollection(JCollection* c, JObject* mutex):JObject(getClazz()){
                this->c = c;
                this->mutex = mutex;
            }

            virtual jint size() {
                synchronized(mutex,{
                    return c->size();
                })
            }

            virtual jbool isEmpty() {
                synchronized(mutex,{
                    return c->isEmpty();
                })
            }

            virtual jbool contains(JObject* o) {
                synchronized(mutex,{
                    return c->contains(o);
                })
            }

            virtual JPrimitiveObjectArray* toArray() {
                synchronized(mutex,{
                    return c->toArray();
                })
            }

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a) {
                synchronized (mutex,{
                    return c->toArray(a);
                })
            }

            virtual JIterator* iterator() {
                return c->iterator();
            }

            virtual jbool add(JObject* e) {
                synchronized(mutex,{
                    return c->add(e);
                })
            }

            virtual jbool remove(JObject* o) {
                synchronized(mutex,{
                    return c->remove(o);
                })
            }

            virtual jbool containsAll(JCollection* coll) {
                synchronized(mutex,{
                    return c->containsAll(coll);
                })
            }

            virtual jbool addAll(JCollection* coll) {
                synchronized(mutex,{
                    return c->addAll(coll);
                })
            }

            virtual jbool removeAll(JCollection* coll) {
                synchronized(mutex,{
                    return c->removeAll(coll);
                })
            }

            virtual jbool retainAll(JCollection* coll) {
                synchronized(mutex,{
                    return c->retainAll(coll);
                })
            }

            virtual void clear() {
                synchronized(mutex,{
                    c->clear();
                })
            }

            virtual JString* toString() {
                synchronized(mutex,{
                    if (c!=null){
                        JObject* o=dynamic_cast<JObject*>(c);
                        return o->toString();
                    }
                    return null;
                })
            }

            virtual void writeObject(JObjectOutputStream* s){
                synchronized(mutex,{
                    s->defaultWriteObject();
                })
            }
        };

        jcpp::lang::JClass* JSynchronizedCollection::synchronizedCollectionClazz = null;

        JCollection* JCollections::synchronizedCollection(JCollection* c){
            return new JSynchronizedCollection(c);
        }

        JCollection* JCollections::synchronizedCollection(JCollection* c, JObject* mutex){
            return new JSynchronizedCollection(c,mutex);
        }

        // @Class(canonicalName="java.util.Collections$SynchronizedList", simpleName="Collections$SynchronizedList");
        class JSynchronizedList : public JSynchronizedCollection, public JList{
        private:
        	static const jlong serialVersionUID = -7754090372962971524LL;
        protected:
            JList* list;
        public:
            static jcpp::lang::JClass* getClazz();

            JSynchronizedList(JList* list):JSynchronizedCollection(getClazz(),list){
                this->list = list;
            }

            JSynchronizedList(jcpp::lang::JClass* _class,JList* list):JSynchronizedCollection(_class,list){
                this->list = list;
            }

            JSynchronizedList(JList* list, JObject* mutex):JSynchronizedCollection(getClazz(),list,mutex){
                this->list = list;
            }

            JSynchronizedList(jcpp::lang::JClass* _class,JList* list, JObject* mutex):JSynchronizedCollection(_class,list,mutex){
                this->list = list;
            }

            virtual jint size() {
                return JSynchronizedCollection::size();
            }

            virtual jbool isEmpty() {
                return JSynchronizedCollection::isEmpty();
            }

            virtual jbool contains(JObject* o) {
                return JSynchronizedCollection::contains(o);
            }

            virtual jbool add(JObject* e){
                return JSynchronizedCollection::add(e);
            }

            virtual jbool remove(JObject* o){
                return JSynchronizedCollection::remove(o);
            }

            virtual jbool containsAll(JCollection* c){
                return JSynchronizedCollection::containsAll(c);
            }

            virtual jbool addAll(JCollection* c){
                return JSynchronizedCollection::addAll(c);
            }

            virtual jbool removeAll(JCollection* c){
                return JSynchronizedCollection::removeAll(c);
            }

            virtual jbool retainAll(JCollection* c){
                return JSynchronizedCollection::retainAll(c);
            }

            virtual JPrimitiveObjectArray* toArray(){
                return JSynchronizedCollection::toArray();
            }

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a){
                return JSynchronizedCollection::toArray(a);
            }

            virtual void clear(){
                return JSynchronizedCollection::clear();
            }

            virtual jbool equals(JObject* o) {
                synchronized(mutex,{
                    if (o==this){
                        return true;
                    }
                    return list->equals(o);
                })
            }

            virtual jint hashCode() {
                synchronized(mutex,{
                    return list->hashCode();
                })
            }

            virtual JObject* get(jint index) {
                synchronized(mutex,{
                    return list->get(index);
                })
            }

            virtual JObject* set(jint index, JObject* element) {
                synchronized(mutex,{
                    return list->set(index, element);
                })
            }

            virtual void add(jint index, JObject* element) {
                synchronized(mutex,{
                    list->add(index, element);
                })
            }

            virtual JObject* remove(jint index) {
                synchronized(mutex,{
                    return list->remove(index);
                })
            }

            virtual jint indexOf(JObject* o) {
                synchronized(mutex,{
                    return list->indexOf(o);
                })
            }

            virtual jint lastIndexOf(JObject* o) {
                synchronized(mutex,{
                    return list->lastIndexOf(o);
                })
            }

            virtual jbool addAll(jint index, JCollection* c) {
                synchronized(mutex,{
                    return list->addAll(index, c);
                })
            }

            virtual JIterator* iterator(){
                return JSynchronizedCollection::iterator();
            }

            virtual JListIterator* listIterator() {
                return list->listIterator();
            }

            virtual JListIterator* listIterator(jint index) {
                return list->listIterator(index);
            }

            virtual JList* subList(jint fromIndex, jint toIndex) {
                synchronized(mutex,{
                    return new JSynchronizedList(list->subList(fromIndex, toIndex),mutex);
                })
            }
        };

        // @Class(canonicalName="java.util.Collections$SynchronizedRandomAccessList", simpleName="Collections$SynchronizedRandomAccessList");
        class JSynchronizedRandomAccessList : public JSynchronizedList, public JRandomAccess{
        private:
        	static const jlong serialVersionUID = 1530674583602358482LL;

        public:
            static jcpp::lang::JClass* getClazz();

            JSynchronizedRandomAccessList(JList* list):JSynchronizedList(getClazz(),list) {
            }

            JSynchronizedRandomAccessList(JList* list, JObject* mutex):JSynchronizedList(getClazz(),list,mutex) {
            }

            virtual JList* subList(jint fromIndex, jint toIndex) {
               synchronized(mutex,{
                   return new JSynchronizedRandomAccessList(list->subList(fromIndex, toIndex), mutex);
                })
            }
        };

        JList* JCollections::synchronizedList(JList* list) {
            JObject* o=dynamic_cast<JObject*>(list);
            return (JRandomAccess::getClazz()->isAssignableFrom(o->getClass()) ? new JSynchronizedRandomAccessList(list) : new JSynchronizedList(list));
        }

        JList* JCollections::synchronizedList(JList* list,JObject* mutex){
            JObject* o=dynamic_cast<JObject*>(list);
            return (JRandomAccess::getClazz()->isAssignableFrom(o->getClass()) ? new JSynchronizedRandomAccessList(list,mutex) : new JSynchronizedList(list,mutex));
        }

        // @Class(canonicalName="java.util.Collections$EmptyIterator", simpleName="Collections$EmptyIterator");
        class JEmptyIterator : public JObject, public JIterator{
        public:
            static jcpp::lang::JClass* getClazz();

            JEmptyIterator():JObject(getClazz()){
            }

            virtual jbool hasNext(){
                return false;
            }

            virtual JObject* next(){
                throw new JNoSuchElementException();
            }

            virtual void remove(){
                throw new JIllegalStateException();
            }

            ~JEmptyIterator(){
            }
        };

        // @Class(canonicalName="java.util.Collections$SynchronizedSet", simpleName="Collections$SynchronizedSet");
        class JSynchronizedSet : public JSynchronizedCollection, public JSet {
        private:
        	static const jlong serialVersionUID = 487447009682186044LL;
        public:
            static jcpp::lang::JClass* getClazz();

            JSynchronizedSet(JSet* s):JSynchronizedCollection(getClazz(),s) {
            }

            JSynchronizedSet(JSet* s, JObject* mutex):JSynchronizedCollection(getClazz(),s,mutex) {
            }

            virtual jint size(){
                return JSynchronizedCollection::size();
            }

            virtual jbool isEmpty(){
                return JSynchronizedCollection::isEmpty();
            }

            virtual jbool contains(JObject* o){
                return JSynchronizedCollection::contains(o);
            }

            virtual JIterator* iterator(){
                return JSynchronizedCollection::iterator();
            }

            virtual JPrimitiveObjectArray* toArray(){
                return JSynchronizedCollection::toArray();
            }

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a){
                return JSynchronizedCollection::toArray(a);
            }

            virtual jbool add(JObject* e){
                return JSynchronizedCollection::add(e);
            }

            virtual jbool remove(JObject* o){
                return JSynchronizedCollection::remove(o);
            }

            virtual jbool containsAll(JCollection* c){
                return JSynchronizedCollection::containsAll(c);
            }

            virtual jbool addAll(JCollection* c){
                return JSynchronizedCollection::addAll(c);
            }

            virtual jbool retainAll(JCollection* c){
                return JSynchronizedCollection::retainAll(c);
            }

            virtual jbool removeAll(JCollection* c){
                return JSynchronizedCollection::removeAll(c);
            }

            virtual void clear(){
                JSynchronizedCollection::clear();
            }

            virtual jbool equals(JObject* o) {
                if (this == o){
                    return true;
                }
                synchronized(mutex,{
                    return dynamic_cast<JObject*>(c)->equals(o);
                })
            }

            virtual jint hashCode() {
                synchronized(mutex, {
                    return dynamic_cast<JObject*>(c)->hashCode();
                })
            }
        };

        JSet* JCollections::synchronizedSet(JSet* s) {
            return new JSynchronizedSet(s);
        }

        JSet* JCollections::synchronizedSet(JSet* s, JObject* mutex) {
            return new JSynchronizedSet(s, mutex);
        }

        JIterator* JCollections::emptyIterator(){
            return new JEmptyIterator();
        }

        // @Class(canonicalName="java.util.Collections$EmptyEnumeration", simpleName="Collections$EmptyEnumeration");
        class JEmptyEnumeration : public JObject, public JEnumeration{
        public:
            static jcpp::lang::JClass* getClazz();

            JEmptyEnumeration():JObject(getClazz()){
            }

            virtual jbool hasMoreElements(){
                return false;
            }

            virtual JObject* nextElement(){
                throw new JNoSuchElementException();
            }

            ~JEmptyEnumeration(){
            }
        };

        JEnumeration* JCollections::emptyEnumeration(){
            return new JEmptyEnumeration();
        }

        static jint REVERSE_THRESHOLD =   18;

        void JCollections::reverse(JList* list){
            jint size = list->size();
            JObject* ol=dynamic_cast<JObject*>(list);
            if (size < REVERSE_THRESHOLD || ol->isInstanceOf(JRandomAccess::getClazz())) {
                for (jint i=0, mid=size>>1, j=size-1; i<mid; i++, j--){
                    swap(list, i, j);
                }
            } else {
                JListIterator* fwd = list->listIterator();
                JListIterator* rev = list->listIterator(size);
                for (jint i=0, mid=list->size()>>1; i<mid; i++) {
                    JObject* tmp = fwd->next();
                    fwd->set(rev->previous());
                    rev->set(tmp);
                }
            }
        }

        void JCollections::sort(JList* list,JComparator* c){
            JPrimitiveObjectArray* a = list->toArray();
            JArrays::sort(a, c);
            JListIterator* i = list->listIterator();
            for (jint j=0;j<a->size();j++){
                JObject* e=a->get(j);
                i->next();
                i->set(e);
            }
        }

        void JCollections::swap(JList* l, jint i, jint j) {
            l->set(i, l->set(j, l->get(i)));
        }

        JCollections::~JCollections(){
        }
    }
}
