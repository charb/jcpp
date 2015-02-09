#ifndef JCPP_UTIL_JARRAY_DEQUE_H
#define JCPP_UTIL_JARRAY_DEQUE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/util/JDeque.h"
#include "jcpp/util/JAbstractCollection.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;

namespace jcpp{
    namespace util{
        class JDeqIterator;
        class JDescendingIterator;

    	// @Class(canonicalName="java.util.ArrayDeque", simpleName="ArrayDeque");
        class JCPP_EXPORT JArrayDeque : public JAbstractCollection, public virtual JQueue, public virtual JCloneable, public virtual JSerializable{
        protected:
            static jint MIN_INITIAL_CAPACITY;
            static jlong serialVersionUID;
            //@Transient()
            JPrimitiveObjectArray* elements;
            //@Transient()
            jint head;
            //@Transient()
            jint tail;

            void allocateElements(jint numElements);
            void doubleCapacity();
            JPrimitiveObjectArray* copyElements(JPrimitiveObjectArray* a);
            void checkInvariants();
            jbool deleteItem(jint i);
            virtual void writeObject(JObjectOutputStream* out);
            virtual void readObject(JObjectInputStream* in);

            friend JDeqIterator;
            friend JDescendingIterator;

        public:
            JArrayDeque();

            JArrayDeque(jint n);

            JArrayDeque(JCollection* c);

            static JClass* getClazz();

            virtual void addFirst(JObject* e);

            virtual void addLast(JObject* e);

            virtual jbool offerFirst(JObject* e);

            virtual jbool offerLast(JObject* e);

            virtual JObject* removeFirst();

            virtual JObject* removeLast();

            virtual JObject* pollFirst();

            virtual JObject* pollLast();

            virtual JObject* getFirst();

            virtual JObject* getLast();

            virtual JObject* peekFirst();

            virtual JObject* peekLast();

            virtual jbool removeFirstOccurrence(JObject* o);

            virtual jbool removeLastOccurrence(JObject* o);

            virtual jbool add(JObject* e);

            virtual jbool offer(JObject* e);

            virtual JObject* remove();

            virtual JObject* poll();

            virtual JObject* element();

            virtual JObject* peek();

            virtual void push(JObject* e);

            virtual JObject* pop();

            virtual jint size();

            virtual jbool isEmpty();

            virtual JIterator* iterator();
            
            virtual JIterator* descendingIterator();

            virtual jbool contains(JObject* o);

            virtual jbool remove(JObject* o);

            virtual void clear();

            virtual JPrimitiveObjectArray* toArray();

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a);

            virtual JArrayDeque* clone();

            virtual ~JArrayDeque();
        };
    }
}


#endif
