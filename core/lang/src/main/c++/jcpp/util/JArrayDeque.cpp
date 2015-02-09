#include "jcpp/util/JArrayDeque.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/reflect/JArray.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/util/JCollection.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{

    	jint JArrayDeque::MIN_INITIAL_CAPACITY = 8;

        jlong JArrayDeque::serialVersionUID = 2340985798034038923L;

        void JArrayDeque::allocateElements(jint numElements){
        	jint initialCapacity = MIN_INITIAL_CAPACITY;
	        if (numElements >= initialCapacity) {
	            initialCapacity = numElements;
	            initialCapacity |= (initialCapacity >>  1);
	            initialCapacity |= (initialCapacity >>  2);
	            initialCapacity |= (initialCapacity >>  4);
	            initialCapacity |= (initialCapacity >>  8);
	            initialCapacity |= (initialCapacity >> 16);
	            initialCapacity++;

	            if (initialCapacity < 0){
	                initialCapacity >>= 1;
	            }
	        }
	        elements = new JPrimitiveObjectArray(JObject::getClazz(),initialCapacity);
        }

        void JArrayDeque::doubleCapacity(){
	        jint p = head;
	        jint n = elements->size();
	        jint r = n - p;
	        jint newCapacity = n << 1;
	        if (newCapacity < 0){
	            throw new JIllegalStateException();
	        }
	        JPrimitiveObjectArray* a = new JPrimitiveObjectArray(JObject::getClazz(),newCapacity);
	        JSystem::arraycopy(elements, p, a, 0, r);
	        JSystem::arraycopy(elements, 0, a, r, p);
	        elements = a;
	        head = 0;
	        tail = n;
        }

        JPrimitiveObjectArray* JArrayDeque::copyElements(JPrimitiveObjectArray* a){
			if (head < tail) {
	            JSystem::arraycopy(elements, head, a, 0, size());
	        } else if (head > tail) {
	            jint headPortionLen = elements->size() - head;
	            JSystem::arraycopy(elements, head, a, 0, headPortionLen);
	            JSystem::arraycopy(elements, 0, a, headPortionLen, tail);
	        }
	        return a;
        }

        void JArrayDeque::checkInvariants(){
        }

        jbool JArrayDeque::deleteItem(jint i){
        	checkInvariants();
	        JPrimitiveObjectArray* elements = this->elements;
	        jint mask = elements->size() - 1;
	        jint h = head;
	        jint t = tail;
	        jint front = (i - h) & mask;
	        jint back  = (t - i) & mask;

	        if (front >= ((t - h) & mask)){
	            throw new JConcurrentModificationException();
	        }

	        if (front < back) {
	            if (h <= i) {
	                JSystem::arraycopy(elements, h, elements, h + 1, front);
	            } else { 
	                JSystem::arraycopy(elements, 0, elements, 1, i);
	                elements->set(0, elements->get(mask));
	                JSystem::arraycopy(elements, h, elements, h + 1, mask - h);
	            }
	            elements->set(h, null);
	            head = (h + 1) & mask;
	            return false;

	        } else {
	            if (i < t) {
	                JSystem::arraycopy(elements, i + 1, elements, i, back);
	                tail = t - 1;
	            } else {
	                JSystem::arraycopy(elements, i + 1, elements, i, mask - i);
	                elements->set(mask, elements->get(0));
	                JSystem::arraycopy(elements, 1, elements, 0, t);
	                tail = (t - 1) & mask;
	            }
	            return true;
	        }
        }

        void JArrayDeque::writeObject(JObjectOutputStream* out){
        	out->defaultWriteObject();
	        out->writeInt(size());

	        jint mask = elements->size() - 1;
	        for (jint i = head; i != tail; i = (i + 1) & mask){
	            out->writeObject(elements->get(i));
	        }
        }
        
        void JArrayDeque::readObject(JObjectInputStream* in){
        	in->defaultReadObject();

	        jint size = in->readInt();
	        allocateElements(size);
	        head = 0;
	        tail = size;

	        for (jint i = 0; i < size; i++){
	            elements->set(i, in->readObject());
	        }
        }

        JArrayDeque::JArrayDeque():JAbstractCollection(getClazz()){
        	elements = new JPrimitiveObjectArray(JObject::getClazz(),16);
        	head=0;
        	tail=0;
        }

        JArrayDeque::JArrayDeque(jint n):JAbstractCollection(getClazz()){
        	elements=null;
        	head=0;
        	tail=0;
        	allocateElements(n);
        }

        JArrayDeque::JArrayDeque(JCollection* c):JAbstractCollection(getClazz()){
        	elements=null;
        	head=0;
        	tail=0;
        	allocateElements(c->size());
        	addAll(c);
        }

        void JArrayDeque::addFirst(JObject* e){
	        if (e == null){
	            throw new JNullPointerException();
	        }
	        elements->set((head = (head - 1) & (elements->size() - 1)) , e);
	        if (head == tail){
	            doubleCapacity();
	        }
	    }

        void JArrayDeque::addLast(JObject* e){
        	if (e == null){
	            throw new JNullPointerException();
	        }
	        elements->set(tail, e);
	        if ( (tail = (tail + 1) & (elements->size() - 1)) == head){
	            doubleCapacity();
	        }
        }

        jbool JArrayDeque::offerFirst(JObject* e){
        	addFirst(e);
        	return true;
        }

        jbool JArrayDeque::offerLast(JObject* e){
        	addLast(e);
        	return true;
        }

        JObject* JArrayDeque::removeFirst(){
        	JObject* x = pollFirst();
	        if (x == null){
	            throw new JNoSuchElementException();
	        }
	        return x;
        }

        JObject* JArrayDeque::removeLast(){
        	JObject* x = pollLast();
	        if (x == null){
	            throw new JNoSuchElementException();
	        }
	        return x;
        }

        JObject* JArrayDeque::pollFirst(){
        	jint h = head;
	        JObject* result = elements->get(h);
	        if (result == null){
	            return null;
	        }
	        elements->set(h, null);
	        head = (h + 1) & (elements->size() - 1);
	        return result;
        }

        JObject* JArrayDeque::pollLast(){
        	jint t = (tail - 1) & (elements->size() - 1);
	        JObject* result = elements->get(t);
	        if (result == null){
	            return null;
	        }
	        elements->set(t, null);
	        tail = t;
	        return result;
        }

        JObject* JArrayDeque::getFirst(){
        	JObject* result = elements->get(head);
	        if (result == null){
	            throw new JNoSuchElementException();
	        }
	        return result;
        }

        JObject* JArrayDeque::getLast(){
        	JObject* result = elements->get((tail - 1) & (elements->size() - 1));
	        if (result == null){
	            throw new JNoSuchElementException();
	        }
	        return result;
        }

        JObject* JArrayDeque::peekFirst(){
        	return elements->get(head);
        }

        JObject* JArrayDeque::peekLast(){
        	return elements->get((tail - 1) & (elements->size() - 1));
        }

        jbool JArrayDeque::removeFirstOccurrence(JObject* o){
        	if (o == null){
	            return false;
	        }
	        jint mask = elements->size() - 1;
	        jint i = head;
	        JObject* x=null;
	        while ( (x = elements->get(i)) != null) {
	            if (o->equals(x)) {
	                deleteItem(i);
	                return true;
	            }
	            i = (i + 1) & mask;
	        }
	        return false;
        }

        jbool JArrayDeque::removeLastOccurrence(JObject* o){
        	if (o == null){
	            return false;
	        }
	        jint mask = elements->size() - 1;
	        jint i = (tail - 1) & mask;
	        JObject* x=null;
	        while ( (x = elements->get(i)) != null) {
	            if (o->equals(x)) {
	                deleteItem(i);
	                return true;
	            }
	            i = (i - 1) & mask;
	        }
	        return false;
        }

        jbool JArrayDeque::add(JObject* e){
        	addLast(e);
        	return true;
        }

        jbool JArrayDeque::offer(JObject* e){
        	return offerLast(e);
        }

        JObject* JArrayDeque::remove(){
        	return removeFirst();
        }

        JObject* JArrayDeque::poll(){
        	return pollFirst();
        }

        JObject* JArrayDeque::element(){
        	return getFirst();
        }

        JObject* JArrayDeque::peek(){
        	return peekFirst();
        }

        void JArrayDeque::push(JObject* e){
        	addFirst(e);
        }

        JObject* JArrayDeque::pop(){
        	return removeFirst();
        }

        jint JArrayDeque::size(){
        	return (tail - head) & (elements->size() - 1);
        }

        jbool JArrayDeque::isEmpty(){
        	return head == tail;
        }

        // @Class(canonicalName="java.util.ArrayDeque$DeqIterator", simpleName="ArrayDeque$DeqIterator");
        class JCPP_EXPORT JDeqIterator : public JObject, public virtual JIterator{
        protected:
        	JArrayDeque* deque;
        	jint cursor;
			jint fence;
			jint lastRet;

		public:
            JDeqIterator(JArrayDeque* deque){
            	this->deque=deque;
            	cursor=deque->head;
            	fence=deque->tail;
            	lastRet=-1;
            }

            static JClass* getClazz();

            virtual jbool hasNext() {
	            return cursor != fence;
	        }

	        virtual JObject* next() {
	            if (cursor == fence){
	                throw new JNoSuchElementException();
	            }
	            JObject* result = deque->elements->get(cursor);
	            if (deque->tail != fence || result == null){
	                throw new JConcurrentModificationException();
	        	}
	            lastRet = cursor;
	            cursor = (cursor + 1) & (deque->elements->size() - 1);
	            return result;
	        }

	        virtual void remove() {
	            if (lastRet < 0){
	                throw new JIllegalStateException();
	            }
	            if (deque->deleteItem(lastRet)) {
	                cursor = (cursor - 1) & (deque->elements->size() - 1);
	                fence = deque->tail;
	            }
	            lastRet = -1;
	        }
        };

        JIterator* JArrayDeque::iterator(){
        	return new JDeqIterator(this);
        }

        // @Class(canonicalName="java.util.ArrayDeque$DescendingIterator", simpleName="ArrayDeque$DescendingIterator");
        class JCPP_EXPORT JDescendingIterator : public JObject, public virtual JIterator{
        protected:
        	JArrayDeque* deque;
        	jint cursor;
			jint fence;
			jint lastRet;

		public:
            JDescendingIterator(JArrayDeque* deque){
            	this->deque=deque;
            	cursor=deque->tail;
            	fence=deque->head;
            	lastRet=-1;
            }

            static JClass* getClazz();

            virtual jbool hasNext() {
	            return cursor != fence;
	        }

	        virtual JObject* next() {
	            if (cursor == fence){
	                throw new JNoSuchElementException();
	            }
	            cursor = (cursor - 1) & (deque->elements->size() - 1);
	            JObject* result = deque->elements->get(cursor);
	            if (deque->head != fence || result == null){
	                throw new JConcurrentModificationException();
	            }
	            lastRet = cursor;
	            return result;
	        }

	        virtual void remove() {
	            if (lastRet < 0){
	                throw new JIllegalStateException();
	            }
	            if (!deque->deleteItem(lastRet)) {
	                cursor = (cursor + 1) & (deque->elements->size() - 1);
	                fence = deque->head;
	            }
	            lastRet = -1;
	        }
        };
        
        JIterator* JArrayDeque::descendingIterator(){
        	return new JDescendingIterator(this);
        }

        jbool JArrayDeque::contains(JObject* o){
	        if (o == null){
	            return false;
	        }
	        jint mask = elements->size() - 1;
	        jint i = head;
	        JObject* x=null;
	        while ( (x = elements->get(i)) != null) {
	            if (o->equals(x)){
	                return true;
	            }
	            i = (i + 1) & mask;
	        }
	        return false;
	    }

        jbool JArrayDeque::remove(JObject* o){
	        return removeFirstOccurrence(o);
	    }

        void JArrayDeque::clear(){
	        jint h = head;
	        jint t = tail;
	        if (h != t) {
	            head = tail = 0;
	            jint i = h;
	            jint mask = elements->size() - 1;
	            do {
	                elements->set(i, null);
	                i = (i + 1) & mask;
	            } while (i != t);
	        }
	    }

        JPrimitiveObjectArray* JArrayDeque::toArray(){
	        return copyElements(new JPrimitiveObjectArray(JObject::getClazz(),size()));
	    }

        JPrimitiveObjectArray* JArrayDeque::toArray(JPrimitiveObjectArray* a){
        	jint isize = size();
	        if (a->size() < isize){
	            a = dynamic_cast<JPrimitiveObjectArray*>(JArray::newInstance(a->getClass()->getComponentType(), isize));
	        }
	        copyElements(a);
	        if (a->size() > isize){
	            a->set(isize, null);
	        }
	        return a;
        }

        JArrayDeque* JArrayDeque::clone(){
        	return new JArrayDeque(this);
        }

        JArrayDeque::~JArrayDeque(){
        }
    }
}
