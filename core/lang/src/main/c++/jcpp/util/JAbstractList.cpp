#include "jcpp/util/JAbstractList.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JListIterator.h"
#include "jcpp/util/JRandomAccess.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

        // @Class(canonicalName="java.util.AbstractList$Itr", simpleName="AbstractList$Itr");
        class JItr : public JObject ,public JIterator{
        protected:
            JAbstractList* list;
            jint cursor;
            jint lastRet;
            jint expectedModCount;

        public:

            JItr(JAbstractList* list,jcpp::lang::JClass* _class):JObject(_class){
                this->list=list;
                cursor = 0;
                lastRet = -1;
                expectedModCount = list->modCount;
            }

            JItr(JAbstractList* list):JObject(getClazz()){
                this->list=list;
                cursor = 0;
                lastRet = -1;
                expectedModCount = list->modCount;
            }

            static jcpp::lang::JClass* getClazz();

            virtual jbool hasNext() {
                return cursor != list->size();
            }

            virtual JObject* next() {
                checkForComodification();
                try {
                    jint i=cursor;
                    JObject* next = list->get(i);
                    lastRet = i;
                    cursor=i+1;
                    return next;
                } catch (JIndexOutOfBoundsException* e) {
                    checkForComodification();
                    throw new JNoSuchElementException();
                }
            }

            virtual void remove() {
                if (lastRet <0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    list->remove(lastRet);
                    if (lastRet < cursor){
                        cursor--;
                    }
                    lastRet = -1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* e) {
                    throw new JConcurrentModificationException();
                }
            }

            virtual void checkForComodification() {
                if (list->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        // @Class(canonicalName="java.util.AbstractList$ListItr", simpleName="AbstractList$ListItr");
        class JListItr : public JItr, public JListIterator {
        public:

            JListItr(JAbstractList* list,jint index) : JItr(list,getClazz()){
                cursor = index;
            }

            static jcpp::lang::JClass* getClazz();

            virtual jbool hasNext(){
                return JItr::hasNext();
            }

            virtual JObject* next(){
                return JItr::next();
            }

            virtual void remove(){
                JItr::remove();
            }

            virtual jbool hasPrevious() {
                return cursor != 0;
            }

            virtual JObject* previous() {
                checkForComodification();
                try {
                    jint i = cursor - 1;
                    JObject* previous = list->get(i);
                    lastRet = cursor = i;
                    return previous;
                } catch (JIndexOutOfBoundsException* e) {
                    checkForComodification();
                    throw new JNoSuchElementException();
                }
            }

            virtual jint nextIndex() {
                return cursor;
            }

            virtual jint previousIndex() {
                return cursor-1;
            }

            virtual void set(JObject* e) {
                if (lastRet<0){
                    throw new JIllegalStateException();
                }
                checkForComodification();
                try {
                    list->set(lastRet, e);
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }

            virtual void add(JObject* e) {
                checkForComodification();
                try {
                    jint i=cursor;
                    list->add(i, e);
                    lastRet = -1;
                    cursor=i+1;
                    expectedModCount = list->modCount;
                } catch (JIndexOutOfBoundsException* ex) {
                    throw new JConcurrentModificationException();
                }
            }
        };

        // @Class(canonicalName="java.util.SubList", simpleName="SubList");
        class JSubList : public JAbstractList {
        protected:
            JAbstractList* l;
            jint offset;
            jint isize;
            jint expectedModCount;
        public:

            static jcpp::lang::JClass* getClazz();

            JSubList(JAbstractList* list, jint fromIndex, jint toIndex) : JAbstractList(getClazz()){
                if (fromIndex < 0){
                    throw new JIndexOutOfBoundsException();
                }
                if (toIndex > list->size()){
                    throw new JIndexOutOfBoundsException();
                }
                if (fromIndex > toIndex){
                    throw new JIllegalArgumentException();
                }
                l = list;
                offset = fromIndex;
                isize = toIndex - fromIndex;
                expectedModCount = l->modCount;
            }

            JSubList(jcpp::lang::JClass* _class,JAbstractList* list, jint fromIndex, jint toIndex) : JAbstractList(_class){
                if (fromIndex < 0){
                    throw new JIndexOutOfBoundsException();
                }
                if (toIndex > list->size()){
                    throw new JIndexOutOfBoundsException();
                }
                if (fromIndex > toIndex){
                    throw new JIllegalArgumentException();
                }
                l = list;
                offset = fromIndex;
                isize = toIndex - fromIndex;
                expectedModCount = l->modCount;
            }

            virtual JObject* set(jint index, JObject* element) {
                rangeCheck(index);
                checkForComodification();
                return l->set(index+offset, element);
            }

            virtual JObject* get(jint index) {
                rangeCheck(index);
                checkForComodification();
                return l->get(index+offset);
            }

            virtual jint size() {
                checkForComodification();
                return isize;
            }

            virtual void incrementSize(){
                isize++;
            }

            virtual void decrementSize(){
                isize--;
            }

            virtual void setExpectedModCount(jint expectedModCount){
                this->expectedModCount=expectedModCount;
            }

            virtual void add(jint index, JObject* element) {
                if (index<0 || index>isize){
                    throw new JIndexOutOfBoundsException();
                }
                checkForComodification();
                l->add(index+offset, element);
                expectedModCount = l->modCount;
                isize++;
                modCount++;
            }

            virtual JObject* remove(jint index) {
                rangeCheck(index);
                checkForComodification();
                JObject* result = l->remove(index+offset);
                expectedModCount = l->modCount;
                isize--;
                modCount++;
                return result;
            }

            virtual void removeRange(jint fromIndex, jint toIndex) {
                checkForComodification();
                l->removeRange(fromIndex+offset, toIndex+offset);
                expectedModCount = l->modCount;
                isize -= (toIndex-fromIndex);
                modCount++;
            }

            virtual jbool addAll(JCollection* c) {
                return addAll(isize, c);
            }

            virtual jbool addAll(jint index, JCollection* c) {
                if (index<0 || index>isize){
                    throw new JIndexOutOfBoundsException();
                }
                jint cSize = c->size();
                if (cSize==0){
                    return false;
                }
                checkForComodification();
                l->addAll(offset+index, c);
                expectedModCount = l->modCount;
                isize += cSize;
                modCount++;
                return true;
            }

            virtual JIterator* iterator() {
                return JAbstractList::listIterator();
            }

            virtual JListIterator* listIterator(jint index);

            virtual JList* subList(jint fromIndex, jint toIndex) {
                return new JSubList(this, fromIndex, toIndex);
            }

            virtual void rangeCheck(jint index) {
                if (index<0 || index>=isize){
                    throw new JIndexOutOfBoundsException();
                }
            }

            virtual void checkForComodification() {
                if (l->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }
            }
        };

        // @Class(canonicalName="java.util.RandomAccessSubList", simpleName="RandomAccessSubList");
        class JRandomAccessSubList: public JSubList, public JRandomAccess {
        public:
            JRandomAccessSubList(JAbstractList* list, jint fromIndex, jint toIndex) : JSubList(getClazz(),list,fromIndex,toIndex){
            }

            static jcpp::lang::JClass* getClazz();

            virtual JList* subList(jint fromIndex, jint toIndex) {
                return new JRandomAccessSubList(this, fromIndex, toIndex);
            }
        };

        // @Class(canonicalName="java.util.SubList$ListIterator", simpleName="SubList$ListIterator");
        class JListIteratorImpl : public JListIterator, public JObject {
            protected:
                JSubList* l;
                JListIterator* i;
                jint index;
                jint offset;

            public:
                static jcpp::lang::JClass* getClazz();

                JListIteratorImpl(JSubList* l,jint index,jint offset):JObject(getClazz()){
                    this->l=l;
                    this->index=index;
                    this->offset=offset;
                    i= l->listIterator(index+offset);
                }

                virtual jbool hasNext() {
                    return nextIndex() < l->size();
                }

                virtual JObject* next() {
                    if (hasNext()){
                        return i->next();
                    }else{
                        throw new JNoSuchElementException();
                    }
                    return null;
                }

                virtual jbool hasPrevious() {
                    return previousIndex() >= 0;
                }

                virtual JObject* previous() {
                    if (hasPrevious()){
                        return i->previous();
                    }else{
                        throw new JNoSuchElementException();
                    }
                    return null;
                }

                virtual jint nextIndex() {
                    return i->nextIndex() - offset;
                }

                virtual jint previousIndex() {
                    return i->previousIndex() - offset;
                }

                virtual void remove() {
                    i->remove();
                    l->setExpectedModCount(l->modCount);
                    l->decrementSize();
                }

                virtual void set(JObject* e) {
                    i->set(e);
                }

                virtual void add(JObject* e) {
                    i->add(e);
                    l->setExpectedModCount(l->modCount);
                    l->incrementSize();
                }

                ~JListIteratorImpl(){
                }
        };

        JListIterator* JSubList::listIterator(jint index) {
            checkForComodification();
            if (index<0 || index>isize){
                throw new JIndexOutOfBoundsException();
            }
            return new JListIteratorImpl(this,index,offset);
        }

        JAbstractList::JAbstractList(jcpp::lang::JClass* _class):JAbstractCollection(_class){
            this->modCount=0;
        }

        jbool JAbstractList::isEmpty(){
            return JAbstractCollection::isEmpty();
        }

        jbool JAbstractList::add(JObject* e){
            add(size(), e);
            return true;
        }

        JObject* JAbstractList::set(jint index, JObject* obj){
            throw new JUnsupportedOperationException();
        }

        void JAbstractList::add(jint index, JObject* obj){
            throw new JUnsupportedOperationException();
        }

        jbool JAbstractList::remove(JObject* o){
            return JAbstractCollection::remove(o);
        }

        JObject* JAbstractList::remove(jint index){
            throw new JUnsupportedOperationException();
        }

        jbool JAbstractList::contains(JObject* o){
            return JAbstractCollection::contains(o);
        }

        jbool JAbstractList::containsAll(JCollection* c){
            return JAbstractCollection::containsAll(c);
        }

        jbool JAbstractList::removeAll(JCollection* c){
            return JAbstractCollection::removeAll(c);
        }

        jbool JAbstractList::retainAll(JCollection* c){
            return JAbstractCollection::retainAll(c);
        }

        jint JAbstractList::indexOf(JObject* o){
            JListIterator* e = listIterator();
            if (o==null) {
                while (e->hasNext()){
                    if (e->next()==null){
                        jint index=e->previousIndex();
                        return index;
                    }
                }
            } else {
                while (e->hasNext()){
                    if (o->equals(e->next())){
                        jint index=e->previousIndex();
                        return index;
                    }
                }
            }
            return -1;
        }

        jint JAbstractList::lastIndexOf(JObject* o){
            JListIterator* e = listIterator(size());
            if (o==null) {
                while (e->hasPrevious()){
                    if (e->previous()==null){
                        jint index=e->nextIndex();
                        return index;
                    }
                }
            } else {
                while (e->hasPrevious()){
                    if (o->equals(e->previous())){
                        jint index=e->nextIndex();
                        return index;
                    }
                }
            }
            return -1;
        }

        void JAbstractList::clear(){
            removeRange(0, size());
        }

        jbool JAbstractList::addAll(JCollection* c) {
        	return JAbstractCollection::addAll(c);
        }

        jbool JAbstractList::addAll(jint index, JCollection* c){
            jbool modified = false;
            JIterator* e = c->iterator();
            while (e->hasNext()) {
                add(index++, e->next());
                modified = true;
            }
            return modified;
        }

        JPrimitiveObjectArray* JAbstractList::toArray(){
            return JAbstractCollection::toArray();
        }

        JPrimitiveObjectArray* JAbstractList::toArray(JPrimitiveObjectArray* a){
            return JAbstractCollection::toArray(a);
        }

        JIterator* JAbstractList::iterator() {
            return new JItr(this);
        }

        JListIterator* JAbstractList::listIterator() {
            return listIterator(0);
        }

        JListIterator* JAbstractList::listIterator(jint index){
            if (index<0 || index>size()){
                throw new JIndexOutOfBoundsException(new JString("Index: "+index));
            }
            return new JListItr(this,index);
        }

        JList* JAbstractList::subList(jint fromIndex, jint toIndex){
            if (JRandomAccess::getClazz()->isAssignableFrom(getClass())){
                return new JRandomAccessSubList(this,fromIndex,toIndex);
            }
            return new JSubList(this,fromIndex,toIndex);
        }

        jbool JAbstractList::equals(JObject* o){
            if (o == this){
                return true;
            }
            if ((o == null) || !JList::getClazz()->isAssignableFrom(o->getClass())){
                return false;
            }
            JListIterator* e1 = listIterator();
            JList* l2=dynamic_cast<JList*>(o);
            JListIterator* e2 = l2->listIterator();
            while (e1->hasNext() && e2->hasNext()) {
                JObject* o1 = e1->next();
                JObject* o2 = e2->next();
                if (!(o1==null ? o2==null : o1->equals(o2))){
                    return false;
                }
            }
            jbool eq=!(e1->hasNext() || e2->hasNext());
            return eq;
        }

        jint JAbstractList::hashCode(){
            jint h = 1;
            JIterator* i = iterator();
            while (i->hasNext()) {
                JObject* obj = i->next();
                h = 31*h + (obj==null ? 0 : obj->hashCode());
            }
            return h;
        }

        void JAbstractList::removeRange(jint fromIndex, jint toIndex){
            JListIterator* it = listIterator(fromIndex);
            for (jint i=0, n=toIndex-fromIndex; i<n; i++) {
                it->next();
                it->remove();
            }
        }

        JAbstractList::~JAbstractList(){
        }
    }
}
