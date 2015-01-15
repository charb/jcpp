#include "jcpp/util/JVector.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/util/JCollections.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JOutOfMemoryError.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{

        JVector::JVector(jint i,jint c):JAbstractList(getClazz()){
            items=new JPrimitiveObjectArray(JObject::getClazz(),i);
            elementCount=new JPrimitiveInt(0);
            capacityIncrement=new JPrimitiveInt(c);
        }

        JVector::JVector(JCollection* c):JAbstractList(getClazz()){
            items=c->toArray();
            elementCount=new JPrimitiveInt(items->size());
            capacityIncrement=new JPrimitiveInt(0);
        }

        jint JVector::getModCount(){
            synchronized(this,{
                jint i=modCount;
                return i;
            })
        }

        void JVector::copyInto(JPrimitiveObjectArray* anArray) {
            synchronized(this,{
                JSystem::arraycopy(items, 0, anArray, 0, elementCount->get());
            })
        }

        void JVector::trimToSize(){
            synchronized(this,{
                modCount++;
                jint oldCapacity = items->size();
                if (elementCount->get() < oldCapacity) {
                    items = JArrays::copyOf(items, elementCount->get());
                }
            })
        }

        void JVector::ensureCapacity(jint c){
            synchronized(this,{
                if (c > 0) {
                    modCount++;
                    ensureCapacityHelper(c);
                }
            })
        }

        void JVector::ensureCapacityHelper(jint c) {
            if (c - items->size() > 0){
                grow(c);
            }
        }

        jint JVector::MAX_ARRAY_SIZE = JInteger::MAX_VALUE - 8;

        void JVector::grow(jint c) {
            jint oldCapacity = items->size();
            jint newCapacity = oldCapacity + ((capacityIncrement->get() > 0) ? capacityIncrement->get() : oldCapacity);
            if (newCapacity - c < 0){
                newCapacity = c;
            }
            if (newCapacity - MAX_ARRAY_SIZE > 0){
                newCapacity = hugeCapacity(c);
            }
            items = JArrays::copyOf(items, newCapacity);
        }

        jint JVector::hugeCapacity(jint minCapacity) {
            if (minCapacity < 0){
                throw new JOutOfMemoryError();
            }
            return (minCapacity > MAX_ARRAY_SIZE) ? JInteger::MAX_VALUE : MAX_ARRAY_SIZE;
        }

        void JVector::setSize(jint newSize){
            synchronized(this,{
                modCount++;
                if (newSize > elementCount->get()) {
                    ensureCapacityHelper(newSize);
                } else {
                    for (jint i = newSize ; i < elementCount->get() ; i++) {
                        items->set(i,null);
                    }
                }
                elementCount->set(newSize);
            })
        }

        jint JVector::capacity(){
            synchronized(this,{
                return items->size();
            })
        }

        jint JVector::size() {
            synchronized(this,{
                return elementCount->get();
            })
        }

        jbool JVector::isEmpty() {
            synchronized(this,{
                return elementCount->get()==0;
            })
        }

        // @Class(canonicalName="java.util.Vector$Enumeration", simpleName="Vector$Enumeration");
        class JEnumerationImpl : public JObject ,public JEnumeration{
        protected:
            JVector* v;
            jint count;

        public:
            JEnumerationImpl(JVector* v):JObject(getClazz()){
                this->v=v;
                count = 0;
            }

            static jcpp::lang::JClass* getClazz();

            virtual jbool hasMoreElements() {
                return count < v->size();
            }

            virtual JObject* nextElement() {
                JObject* o=null;
                synchronized(v,{
                    if (count < v->size()) {
                        o=v->get(count);
                        count++;
                    }else{
                        throw new JNoSuchElementException(new JString("Vector Enumeration"));
                    }
                    return o;
                })
            }
        };

        JEnumeration* JVector::elements() {
            return new JEnumerationImpl(this);
        }

        jbool JVector::contains(JObject* o){
            return indexOf(o)>=0;
        }

        jint JVector::indexOf(JObject* o){
            return indexOf(o,0);
        }

        jint JVector::indexOf(JObject* o,jint index){
            synchronized(this,{
                jint r=-1;
                if (o == null) {
                    for (jint i = index; i < size(); i++){
                        if (get(i)==null){
                            r=i;
                            break;
                        }
                    }
                } else {
                    for (jint i = 0; i < size(); i++){
                        if (o->equals(get(i))){
                            r=i;
                            break;
                        }
                    }
                }
                return r;
            })
        }

        jint JVector::lastIndexOf(JObject* o){
            synchronized(this,{
                jint index=size()-1;
                jint i=lastIndexOf(o,index);
                return i;
            })
        }

        jint JVector::lastIndexOf(JObject* o,jint index){
            synchronized(this,{
                jint r=-1;
                if (o == null) {
                    for (jint i = index; i >= 0; i--){
                        if (get(i)==null){
                            r=i;
                            break;
                        }
                    }
                } else {
                    for (jint i = index; i >= 0; i--){
                        if (o->equals(get(i))){
                            r=i;
                            break;
                        }
                    }
                }
                return r;
            })
        }

        JObject* JVector::elementAt(jint index) {
            synchronized(this,{
                JObject* r=null;
                if (index >= size()) {
                    throw new JArrayIndexOutOfBoundsException();
                }
                r=get(index);
                return r;
            })
        }

        JObject* JVector::firstElement() {
            synchronized(this,{
                JObject* r=null;
                if (size() == 0) {
                    throw new JNoSuchElementException();
                }
                r=get(0);
                return r;
            })
        }

        JObject* JVector::lastElement() {
            synchronized(this,{
                JObject* r=null;
                if (size() == 0) {
                    throw new JNoSuchElementException();
                }
                r=get(size()-1);
                return r;
            })
        }

        void JVector::setElementAt(JObject* obj, jint index) {
            synchronized(this,{
                if (index >= size()) {
                    throw new JArrayIndexOutOfBoundsException();
                }
                set(index,obj);
            })
        }

        void JVector::removeElementAt(jint index) {
            synchronized(this,{
                modCount++;
                if (index >= size()) {
                    throw new JArrayIndexOutOfBoundsException();
                }else if (index < 0) {
                    throw new JArrayIndexOutOfBoundsException();
                }
                jint j = elementCount->get() - index - 1;
                if (j > 0) {
                    JSystem::arraycopy(items, index + 1, items, index, j);
                }
                elementCount->set(elementCount->get()-1);
                items->set(elementCount->get(),null);
            })
        }

        void JVector::insertElementAt(JObject* obj, jint index) {
            synchronized(this,{
                modCount++;
                if (index > size()) {
                    throw new JArrayIndexOutOfBoundsException();
                }
                ensureCapacityHelper(elementCount->get() + 1);
                JSystem::arraycopy(items, index, items, index + 1, elementCount->get() - index);
                items->set(index, obj);
                elementCount->set(elementCount->get()+1);
            })
        }

        void JVector::addElement(JObject* obj) {
            synchronized(this,{
                modCount++;
                ensureCapacityHelper(elementCount->get() + 1);
                items->set(elementCount->get(), obj);
                elementCount->set(elementCount->get()+1);
            })
        }

        jbool JVector::removeElement(JObject* obj) {
            synchronized(this,{
                modCount++;
                jint i = indexOf(obj);
                if (i >= 0) {
                    removeElementAt(i);
                    return true;
                }
                return false;
            })
        }

        void JVector::removeAllElements() {
            synchronized(this,{
                modCount++;
                for (jint i = 0; i < elementCount->get(); i++){
                    items->set(i,null);
                }
                elementCount->set(0);
            })
        }

        JVector* JVector::clone(){
            synchronized(this,{
                return new JVector(reinterpret_cast<JCollection*>(this));
            })
        }

        JPrimitiveObjectArray* JVector::toArray(){
            synchronized(this,{
                return JArrays::copyOf(items, elementCount->get());
            })
        }

        JPrimitiveObjectArray* JVector::toArray(JPrimitiveObjectArray* a){
            synchronized(this,{
                if (a->size() < elementCount->get()){
                    return JArrays::copyOf(items, elementCount->get(), a->getComponentType());
                }
                JSystem::arraycopy(items, 0, a, 0, elementCount->get());
                if (a->size() > elementCount->get()){
                    a->set(elementCount->get(), null);
                }
                return a;
            })
        }

        JObject* JVector::get(jint index){
            synchronized(this,{
                if (index >= elementCount->get()){
                    throw new JArrayIndexOutOfBoundsException();
                }
                return items->get(index);
            })
        }

        JObject* JVector::set(jint index, JObject* element){
            synchronized(this,{
                if (index >= elementCount->get()){
                    throw new JArrayIndexOutOfBoundsException();
                }
                JObject* oldValue = items->get(index);
                items->set(index,element);
                return oldValue;
            })
        }

        jbool JVector::add(JObject* item){
            synchronized(this,{
                modCount++;
                ensureCapacityHelper(elementCount->get() + 1);
                items->set(elementCount->get(), item);
                elementCount->set(elementCount->get()+1);
                return true;
            })
        }

        jbool JVector::remove(JObject* e){
            return removeElement(e);
        }

        void JVector::add(jint index,JObject* o){
            insertElementAt(o,index);
        }

        JObject* JVector::remove(jint index){
            synchronized(this,{
                modCount++;
                if (index >= elementCount->get()){
                    throw new JArrayIndexOutOfBoundsException();
                }
                JObject* oldValue = items->get(index);
                jint numMoved = elementCount->get() - index - 1;
                if (numMoved > 0){
                    JSystem::arraycopy(items, index+1, items, index,numMoved);
                }
                elementCount->set(elementCount->get()-1);
                items->set(elementCount->get(),null);
                return oldValue;
            })
        }

        void JVector::clear(){
            removeAllElements();
        }

        jbool JVector::containsAll(JCollection *c){
            synchronized(this,{
                return JAbstractList::containsAll(c);
            })
        }

        jbool JVector::addAll(JCollection *c){
            synchronized(this,{
                modCount++;
                JPrimitiveObjectArray* a = c->toArray();
                jint numNew = a->size();
                ensureCapacityHelper(elementCount->get() + numNew);
                JSystem::arraycopy(a, 0, items, elementCount->get(), numNew);
                elementCount->set(elementCount->get()+numNew);
                return numNew != 0;
            })
        }

        jbool JVector::removeAll(JCollection *c){
            synchronized(this,{
                return JAbstractList::removeAll(c);
            })
        }

        jbool JVector::retainAll(JCollection *c){
            synchronized(this,{
                return JAbstractList::retainAll(c);
            })
        }

        jbool JVector::addAll(jint index,JCollection* c){
            synchronized(this,{
                modCount++;
                if (index < 0 || index > elementCount->get()){
                    throw new JArrayIndexOutOfBoundsException();
                }
                JPrimitiveObjectArray* a = c->toArray();
                jint numNew = a->size();
                ensureCapacityHelper(elementCount->get() + numNew);
                jint numMoved = elementCount->get() - index;
                if (numMoved > 0){
                    JSystem::arraycopy(items, index, items, index + numNew,numMoved);
                }
                JSystem::arraycopy(a, 0, items, index, numNew);
                elementCount->set(elementCount->get() + numNew);
                return numNew != 0;
            })
        }

        jbool JVector::equals(JObject *other){
            synchronized(this,{
                return JAbstractList::equals(other);
            })
        }

        jint JVector::hashCode(){
            synchronized(this,{
                return JAbstractList::hashCode();
            })
        }

        JString* JVector::toString(){
            synchronized(this,{
                return JAbstractList::toString();
            })
        }

        JList* JVector::subList(jint fromIndex, jint toIndex){
            return JCollections::synchronizedList(JAbstractList::subList(fromIndex,toIndex),this);
        }

        void JVector::removeRange(jint fromIndex, jint toIndex){
            synchronized(this,{
                modCount++;
                jint numMoved = elementCount->get() - toIndex;
                JSystem::arraycopy(items, toIndex, items, fromIndex, numMoved);

                jint newElementCount = elementCount->get() - (toIndex-fromIndex);
                while (elementCount->get() != newElementCount){
                    elementCount->set(elementCount->get()-1);
                    items->set(elementCount->get(),null);
                }
            })
        }

        void JVector::writeObject(JObjectOutputStream* out){
            JObjectOutputStream::JPutField* fields = out->putFields();
            JPrimitiveObjectArray* data=null;
            synchronized (this, {
                fields->put(new JString("capacityIncrement"), capacityIncrement->get());
                fields->put(new JString("elementCount"), elementCount->get());
                data = items->clone();
            })
            fields->put(new JString("elementData"), data);
            out->writeFields();
        }

        // @Class(canonicalName="java.util.Vector$Itr", simpleName="Vector$Itr");
        class JVectorItr : public JObject, public JIterator {
        protected:
            JVector* v;
            jint cursor;
            jint lastRet;
            jint expectedModCount;

            JVectorItr(jcpp::lang::JClass* _class, JVector* v):JObject(_class){
                this->v=v;
                cursor=0;
                lastRet=-1;
                this->expectedModCount=v->getModCount();
            }

        public:
            static jcpp::lang::JClass* getClazz();

            JVectorItr(JVector* v):JObject(getClazz()){
                this->v=v;
                cursor=0;
                lastRet=-1;
                this->expectedModCount=v->modCount;
            }

            virtual jbool hasNext() {
                return cursor != v->size();
            }

            virtual JObject* next() {
                synchronized(v,{
                    checkForComodification();
                    jint i = cursor;
                    if (i >= v->size()){
                        throw new JNoSuchElementException();
                    }
                    cursor = i + 1;
                    JObject* o=v->get(lastRet = i);
                    return o;
                })
            }

            virtual void remove() {
                if (lastRet == -1){
                    throw new JIllegalStateException();
                }
                synchronized(v,{
                    checkForComodification();
                    v->remove(lastRet);
                    expectedModCount = v->getModCount();
                    cursor = lastRet;
                    lastRet = -1;
                })
            }

            virtual void checkForComodification() {
                if (v->getModCount() != expectedModCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        // @Class(canonicalName="java.util.Vector$ListItr", simpleName="Vector$ListItr");
        class JVectorListItr : public JVectorItr , public JListIterator {
        public:
            static jcpp::lang::JClass* getClazz();

            JVectorListItr(JVector* v, jint index):JVectorItr(getClazz(),v) {
                cursor = index;
            }

            virtual jbool hasNext(){
                return JVectorItr::hasNext();
            }

            virtual JObject* next(){
                return JVectorItr::next();
            }

            virtual void remove(){
                return JVectorItr::remove();
            }

            virtual jbool hasPrevious() {
                return cursor != 0;
            }

            virtual jint nextIndex() {
                return cursor;
            }

            virtual jint previousIndex() {
                return cursor - 1;
            }

            virtual JObject* previous() {
                synchronized(v,{
                    checkForComodification();
                    jint i = cursor - 1;
                    if (i < 0){
                        throw new JNoSuchElementException();
                    }
                    cursor = i;
                    JObject* o=v->get(lastRet = i);
                    return o;
                })
            }

            virtual void set(JObject* e) {
                if (lastRet == -1){
                    throw new JIllegalStateException();
                }
                synchronized(v,{
                    checkForComodification();
                    v->set(lastRet, e);
                })
            }

            virtual void add(JObject* e) {
                jint i = cursor;
                synchronized(v,{
                    checkForComodification();
                    v->add(i, e);
                    expectedModCount = v->getModCount();
                    cursor = i + 1;
                    lastRet = -1;
                })
            }
        };

        JListIterator* JVector::listIterator() {
            synchronized(this,{
                return new JVectorListItr(this,0);
            })
        }

        JListIterator* JVector::listIterator(jint index){
            synchronized(this,{
                return new JVectorListItr(this,index);
            })
        }

        JIterator* JVector::iterator() {
            synchronized(this,{
                return new JVectorItr(this);
            })
        }

        JVector::~JVector(){
        }
    }
}

