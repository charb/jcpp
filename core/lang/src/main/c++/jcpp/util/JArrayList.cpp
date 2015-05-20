#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JOutOfMemoryError.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{

        JArrayList::JArrayList():JAbstractList(getClazz()){
            items=new JPrimitiveObjectArray(JObject::getClazz(),10);
            isize=new JPrimitiveInt(0);
        }

        JArrayList::JArrayList(jint c):JAbstractList(getClazz()){
            items=new JPrimitiveObjectArray(JObject::getClazz(),c);
            isize=new JPrimitiveInt(0);
        }

        JArrayList::JArrayList(JCollection* c):JAbstractList(getClazz()){
            items=c->toArray();
            isize=new JPrimitiveInt(items->size());
        }

        JPrimitiveObjectArray* JArrayList::serialPersistentFields = null;

        JPrimitiveObjectArray* JArrayList::getSerialPersistentFields(){
            if (serialPersistentFields==null){
                serialPersistentFields=new JPrimitiveObjectArray(JObjectStreamField::getClazz(),2);
                serialPersistentFields->set(0,new JObjectStreamField(new JString("elementData"),JPrimitiveObjectArray::getClazz()));
                serialPersistentFields->set(1,new JObjectStreamField(new JString("size"),JPrimitiveInt::getClazz()));
            }
            return serialPersistentFields;
        }

        jint JArrayList::size(){
            return isize->get();
        }

        void JArrayList::trimToSize(){
            modCount++;
            if (isize->get() < items->size()) {
                items = (isize->get() == 0) ? new JPrimitiveObjectArray(JObject::getClazz(),0) : JArrays::copyOf(items, isize->get());
            }
        }

        void JArrayList::ensureCapacity(jint c){
            modCount++;
            if (c > items->size()) {
                ensureExplicitCapacity(c);
            }
        }

        void JArrayList::ensureExplicitCapacity(jint c) {
            modCount++;
            if (c > items->size()){
                grow(c);
            }
        }

        void JArrayList::grow(jint c) {
            jint oldCapacity = items->size();
            jint newCapacity = oldCapacity + (oldCapacity >> 1);
            if (newCapacity - c < 0){
                newCapacity = c;
            }
            if (newCapacity - MAX_ARRAY_SIZE > 0){
                newCapacity = hugeCapacity(c);
            }
            items = JArrays::copyOf(items, c);
        }

        jint JArrayList::MAX_ARRAY_SIZE = JInteger::MAX_VALUE - 8;

        jint JArrayList::hugeCapacity(jint c) {
            if (c < 0){
                throw new JOutOfMemoryError();
            }
            return (c > MAX_ARRAY_SIZE) ? JInteger::MAX_VALUE : MAX_ARRAY_SIZE;
        }

        jbool JArrayList::contains(JObject* o){
            return indexOf(o)>=0;
        }

        jint JArrayList::indexOf(JObject* o){
            if (o == null) {
                for (jint i = 0; i < isize->get(); i++){
                    if (items->get(i)==null){
                        return i;
                    }
                }
            } else {
                for (jint i = 0; i < isize->get(); i++){
                    if (o->equals(items->get(i))){
                        return i;
                    }
                }
            }
            return -1;
        }

        jint JArrayList::lastIndexOf(JObject* o){
            if (o == null) {
                for (jint i = isize->get()-1; i >= 0; i--){
                    if (items->get(i)==null){
                        return i;
                    }
                }
            } else {
                for (jint i = isize->get()-1; i >= 0; i--){
                    if (o->equals(items->get(i))){
                        return i;
                    }
                }
            }
            return -1;
        }

        JObject* JArrayList::set(jint index, JObject* element){
            JObject* old=items->get(index);
            items->set(index,element);
            return old;
        }

        jbool JArrayList::isEmpty(){
            return isize->get()==0;
        }

        JObject* JArrayList::get(jint index){
            return items->get(index);
        }

        jbool JArrayList::add(JObject* item){
            ensureCapacity(isize->get() + 1);
            items->set(isize->get(),item);
            isize->set(isize->get()+1);
            return true;
        }

        void JArrayList::add(jint index,JObject* o){
            ensureCapacity(isize->get() + 1);
            JSystem::arraycopy(items, index, items, index + 1,isize->get() - index);
            items->set(index,o);
            isize->set(isize->get()+1);
        }

        JObject* JArrayList::remove(jint index){
            modCount++;
            JObject* oldValue = items->get(index);
            jint numMoved = isize->get() - index - 1;
            if (numMoved > 0){
                JSystem::arraycopy(items, index+1, items, index,numMoved);
            }
            isize->set(isize->get()-1);
            items->set(isize->get(), null);
            return oldValue;
        }

        jbool JArrayList::remove(JObject* o){
            if (o == null) {
                for (jint index = 0; index < isize->get(); index++)
                    if (items->get(index) == null) {
                        fastRemove(index);
                        return true;
                    }

            } else {
                for (jint index = 0; index < isize->get(); index++)
                    if (o->equals(items->get(index))) {
                        fastRemove(index);
                        return true;
                    }
            }
            return false;
        }

        void JArrayList::fastRemove(jint index) {
            modCount++;
            jint numMoved = isize->get() - index - 1;
            if (numMoved > 0){
                JSystem::arraycopy(items, index+1, items, index,numMoved);
            }
            isize->set(isize->get()-1);
            items->set(isize->get(),null);
        }

        jbool JArrayList::removeAll(JCollection* c){
            return batchRemove(c, false);
        }

        jbool JArrayList::retainAll(JCollection* c){
            return batchRemove(c, true);
            return false;
        }

        jbool JArrayList::batchRemove(JCollection* c, jbool complement) {
            jint r = 0;
            jint w = 0;
            jbool modified = false;

            for (; r < isize->get(); r++){
                if (c->contains(items->get(r)) == complement){
                    items->set(w++, items->get(r));
                }
            }

            if (r != isize->get()) {
                JSystem::arraycopy(items, r,items, w,isize->get() - r);
                w += isize->get() - r;
            }

            if (w != isize->get()) {
                for (jint i = w; i < isize->get(); i++){
                    items->set(i, null);
                }
                modCount += isize->get() - w;
                isize->set(w);
                modified = true;
            }
            return modified;
        }

        void JArrayList::clear(){
            modCount++;
            for (jint i = 0; i < isize->get(); i++){
                items->set(i,null);
            }
            isize->set(0);
        }

        JArrayList* JArrayList::clone(){
            return new JArrayList(reinterpret_cast<JCollection*>(this));
        }

        JPrimitiveObjectArray* JArrayList::toArray(){
            return JArrays::copyOf(items, isize->get());
        }

        JPrimitiveObjectArray* JArrayList::toArray(JPrimitiveObjectArray* a){
            if (a->size() < isize->get()){
                return JArrays::copyOf(items, isize->get(), a->getComponentType());
            }
            JSystem::arraycopy(items, 0, a, 0, isize->get());
            if (a->size() > isize->get()){
                a->set(isize->get(),null);
            }
            return a;
        }

        jbool JArrayList::addAll(JCollection* c){
            JPrimitiveObjectArray* a = c->toArray();
            jint numNew = a->size();
            ensureCapacity(isize->get() + numNew);
            JSystem::arraycopy(a, 0, items, isize->get(), numNew);
            isize->set(isize->get() + numNew);
            return numNew != 0;
        }

        jbool JArrayList::addAll(jint index, JCollection* c){
            rangeCheckForAdd(index);

            JPrimitiveObjectArray* a = c->toArray();
            jint numNew = a->size();
            ensureCapacity(isize->get() + numNew);

            jint numMoved = isize->get() - index;
            if (numMoved > 0){
                JSystem::arraycopy(items, index, items, index + numNew,numMoved);
            }
            JSystem::arraycopy(a, 0, items, index, numNew);
            isize->set(isize->get() + numNew);
            return numNew != 0;
        }

        void JArrayList::removeRange(jint fromIndex, jint toIndex) {
            modCount++;
            jint numMoved = isize->get() - toIndex;
            JSystem::arraycopy(items, toIndex, items, fromIndex,numMoved);

            jint newSize = isize->get() - (toIndex-fromIndex);
            for (jint i = newSize; i < isize->get(); i++) {
                items->set(i,null);
            }
            isize->set(newSize);
        }

        void JArrayList::rangeCheck(jint index) {
            if (index >= isize->get()){
                throw new JIndexOutOfBoundsException();
            }
        }

       void JArrayList::rangeCheckForAdd(jint index) {
            if (index > isize->get() || index < 0){
                throw new JIndexOutOfBoundsException();
            }
        }

        void JArrayList::writeObject(JObjectOutputStream* out){
            JObjectOutputStream::JPutField* fields = out->putFields();
            fields->put(new JString("elementData"), items);
            fields->put(new JString("size"), isize->get());
            out->writeFields();
            out->writeInt(isize->get());
            for (jint i=0;i<items->size();i++){
                out->writeObject(items->get(i));
            }
        }

        void JArrayList::readObject(JObjectInputStream* in){
            JObjectInputStream::JGetField* fields = in->readFields();
            fields->get(new JString("elementData"), (JObject*)null);
            isize->set(fields->get(new JString("size"), (jint)0));
            in->readInt();
            
            if (isize->get() > 0) {
                ensureCapacity(isize->get());
                for (jint i=0; i<isize->get(); i++) {
                    items->set(i,in->readObject());
                }
            }
        }



        // @Class(canonicalName="java.util.ArrayList$Itr", simpleName="ArrayList$Itr");
        class JArrayListItr : public JIterator, public JObject {
        private:
        	 static jcpp::lang::JClass* arrayListItrClazz;
        protected:
            JArrayList* list;
            jint cursor;
            jint lastRet;
            jint expectedModCount;

            JArrayListItr(JArrayList* list,jcpp::lang::JClass* _class):JObject(_class){
                this->list=list;
                this->cursor=0;
                this->lastRet=-1;
                this->expectedModCount=list->modCount;
            }

        public:
            JArrayListItr(JArrayList* list):JObject(getClazz()){
                this->list=list;
                this->cursor=0;
                this->lastRet=-1;
                this->expectedModCount=list->modCount;
            }

            static jcpp::lang::JClass* getClazz();

            virtual jbool hasNext() {
                return cursor != list->size();
            }

            virtual JObject* next() {
                checkForComodification();
                jint i = cursor;
                if (i >= list->size()){
                    throw new JNoSuchElementException();
                }
                cursor = i + 1;
                return list->get((lastRet = i));
            }

            virtual void remove() {
                if (lastRet < 0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    list->remove(lastRet);
                    cursor = lastRet;
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            virtual void checkForComodification() {
                if (list->modCount != expectedModCount){
                   throw new JConcurrentModificationException();
                }
            }
        };
        jcpp::lang::JClass* JArrayListItr::arrayListItrClazz = null;



        // @Class(canonicalName="java.util.ArrayList$ListItr", simpleName="ArrayList$ListItr");
        class JArrayListListItr : public JArrayListItr , public JListIterator {
        private:
        	 static jcpp::lang::JClass* arrayListListItrClazz;
        public:
            static jcpp::lang::JClass* getClazz();

            JArrayListListItr(JArrayList* list,jint index):JArrayListItr(list,getClazz()){
                cursor = index;
            }

            virtual jbool hasNext(){
                return JArrayListItr::hasNext();
            }

            virtual JObject* next(){
                return JArrayListItr::next();
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
                checkForComodification();
                jint i = cursor - 1;
                if (i < 0){
                    throw new JNoSuchElementException();
                }
                cursor = i;
                return list->get((lastRet = i));
            }

            virtual void set(JObject* e) {
                if (lastRet < 0){
                    throw new JIllegalStateException();
                }
                try {
                    list->set(lastRet, e);
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            virtual void add(JObject* e) {
                checkForComodification();
                try {
                    jint i = cursor;
                    list->add(i, e);
                    cursor = i + 1;
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            virtual void remove(){
                JArrayListItr::remove();
            }
        };

        jcpp::lang::JClass* JArrayListListItr::arrayListListItrClazz = null;

        // @Class(canonicalName="java.util.ArrayList$SubList", simpleName="ArrayList$SubList");
        class JArrayListSubList : public JAbstractList, public JRandomAccess {
        protected:
            JArrayList* list;
            JAbstractList* parent;
            jint parentOffset;
            jint offset;
            jint isize;
            friend class JArrayListSubListIterator;

        public:
            static jcpp::lang::JClass* getClazz();

            JArrayListSubList(JArrayList* list,JAbstractList* parent, jint offset, jint fromIndex, jint toIndex) : JAbstractList(getClazz()){
                this->list=list;
                this->parent = parent;
                this->parentOffset = fromIndex;
                this->offset = offset + fromIndex;
                this->isize = toIndex - fromIndex;
                this->modCount = list->modCount;
            }

            virtual JObject* set(jint index, JObject* e) {
                rangeCheck(index);
                checkForComodification();
                JObject* oldValue = list->get(offset + index);
                list->set(offset + index,e);
                return oldValue;
            }

            virtual JObject* get(jint index) {
                rangeCheck(index);
                checkForComodification();
                return list->get(offset + index);
            }

            virtual jint size() {
                checkForComodification();
                return isize;
            }

            virtual void add(jint index, JObject* e) {
                rangeCheckForAdd(index);
                checkForComodification();
                parent->add(parentOffset + index, e);
                modCount = parent->modCount;
                isize++;
            }

            virtual JObject* remove(jint index) {
                rangeCheck(index);
                checkForComodification();
                JObject* result = parent->remove(parentOffset + index);
                this->modCount = parent->modCount;
                isize--;
                return result;
            }

            virtual void removeRange(jint fromIndex, jint toIndex) {
                checkForComodification();
                parent->removeRange(parentOffset + fromIndex,parentOffset + toIndex);
                this->modCount = parent->modCount;
                this->isize -= toIndex - fromIndex;
            }

            virtual jbool addAll(JCollection* c) {
                return addAll(isize, c);
            }

            virtual jbool addAll(jint index, JCollection* c) {
                rangeCheckForAdd(index);
                jint cSize = c->size();
                if (cSize==0){
                    return false;
                }
                checkForComodification();
                parent->addAll(parentOffset + index, c);
                modCount = parent->modCount;
                isize += cSize;
                return true;
            }

            virtual JIterator* iterator() {
                return listIterator();
            }

            virtual JListIterator* listIterator() {
                return JAbstractList::listIterator();
            }

            virtual JListIterator* listIterator(jint index);

            virtual JList* subList(jint fromIndex, jint toIndex) {
                return new JArrayListSubList(list,this, offset, fromIndex, toIndex);
            }

            virtual void rangeCheck(jint index) {
                if (index < 0 || index >= isize){
                    throw new JIndexOutOfBoundsException(outOfBoundsMsg(index));
                }
            }

            virtual void rangeCheckForAdd(jint index) {
                if (index < 0 || index > isize){
                    throw new JIndexOutOfBoundsException(outOfBoundsMsg(index));
                }
            }

            virtual JString* outOfBoundsMsg(jint index) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append("Index: ")->append(index)->append(", Size: ")->append(isize);
                return builder->toString();
            }

            virtual void checkForComodification() {
                if (list->modCount != this->modCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        // @Class(canonicalName="java.util.ArrayList$SubList$ListIterator", simpleName="ArrayList$SubList$ListIterator");
        class JArrayListSubListIterator : public JObject, public JListIterator {
        protected:
            JArrayList* list;
            JArrayListSubList* sublist;
            jint cursor;
            jint lastRet;
            jint expectedModCount;
            jint offset;
        public:
            static jcpp::lang::JClass* getClazz();

            JArrayListSubListIterator(JArrayList* list,JArrayListSubList* sublist,jint index,jint offset):JObject(getClazz()){
                this->list=list;
                this->sublist=sublist;
                cursor = index;
                this->offset=offset;
                lastRet = -1;
                expectedModCount = list->modCount;
            }

            virtual jbool hasNext() {
                return cursor != sublist->size();
            }

            virtual JObject* next() {
                checkForComodification();
                jint i = cursor;
                if (i >= sublist->size()){
                    throw new JNoSuchElementException();
                }
                cursor = i + 1;
                return list->get(offset + (lastRet = i));
            }

            virtual jbool hasPrevious() {
                return cursor != 0;
            }

            virtual JObject* previous() {
                checkForComodification();
                jint i = cursor - 1;
                if (i < 0){
                    throw new JNoSuchElementException();
                }
                cursor = i;
                return list->get(offset + (lastRet = i));
            }

            virtual jint nextIndex() {
                return cursor;
            }

            virtual jint previousIndex() {
                return cursor - 1;
            }

            virtual void remove() {
                if (lastRet < 0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    sublist->remove(lastRet);
                    cursor = lastRet;
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            virtual void set(JObject* e) {
                if (lastRet < 0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    list->set(offset + lastRet, e);
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            virtual void add(JObject* e) {
                checkForComodification();
                try {
                    jint i = cursor;
                    sublist->add(i, e);
                    cursor = i + 1;
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            virtual void checkForComodification() {
                if (expectedModCount != list->modCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        JListIterator* JArrayListSubList::listIterator(jint index) {
            checkForComodification();
            rangeCheckForAdd(index);
            return new JArrayListSubListIterator(list,this,index,this->offset);
        }

        JListIterator* JArrayList::listIterator(){
            return new JArrayListListItr(this,0);
        }

        JIterator* JArrayList::iterator(){
            return new JArrayListItr(this);
        }

        JList* JArrayList::subList(jint fromIndex, jint toIndex){
            if (fromIndex < 0){
                throw new JIndexOutOfBoundsException(new JString("fromIndex = "+fromIndex));
            }
            if (toIndex > size()){
                throw new JIndexOutOfBoundsException(new JString("toIndex = "+ toIndex));
            }
            if (fromIndex > toIndex){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("fromIndex=")->append(fromIndex)->append("> toIndex=")->append(toIndex);
                throw new JIllegalArgumentException(builder->toString());
            }
            return new JArrayListSubList(this,this, 0, fromIndex, toIndex);
        }

        JArrayList::~JArrayList(){
        }
    }
}
