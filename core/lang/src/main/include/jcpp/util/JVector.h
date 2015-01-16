#ifndef JCPP_UTIL_JVECTOR_H
#define JCPP_UTIL_JVECTOR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/io/JExternalizable.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/util/JAbstractList.h"
#include "jcpp/util/JRandomAccess.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/util/JEnumeration.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
    	class JVectorClass;
    	class JVectorItr;
    	class JVectorListItr;

    	// @Class(canonicalName="java.util.Vector", simpleName="Vector");
        class JCPP_EXPORT JVector : public JAbstractList, public JRandomAccess, public JSerializable, public JCloneable{
        private:
        	static const jlong serialVersionUID = -2767605614048989439LL;

        protected:
            JPrimitiveObjectArray* elementData;
            JPrimitiveInt* elementCount;
            JPrimitiveInt* capacityIncrement;
            static jint MAX_ARRAY_SIZE;
            
            virtual jint getModCount();
            virtual void ensureCapacityHelper(jint c);
            virtual void grow(jint c);
            virtual jint hugeCapacity(jint minCapacity);
            virtual void writeObject(JObjectOutputStream* out);
            friend class JVectorClass;
            friend class JVectorItr;
            friend class JVectorListItr;

        public:
            JVector(jint initialCapacity);

            JVector(jint initialCapacity, jint capacityIncrement);

            JVector(JCollection* c);

            JVector();

            static jcpp::lang::JClass* getClazz();

            virtual void copyInto(JPrimitiveObjectArray* anArray);

            virtual void trimToSize();

            virtual void ensureCapacity(jint minCapacity);

            virtual void setSize(jint newSize);

            virtual jint capacity();

            virtual jint size();

            virtual jbool isEmpty();

            virtual JIterator* iterator();

            virtual JListIterator* listIterator();

            virtual JListIterator* listIterator(jint index);

            virtual JEnumeration* elements();

            virtual jbool contains(JObject* o);

            virtual jint indexOf(JObject* o);

            virtual jint indexOf(JObject* o,jint index);

            virtual jint lastIndexOf(JObject* o);

            virtual jint lastIndexOf(JObject* o,jint index);

            virtual JObject* elementAt(jint index);

            virtual JObject* firstElement();

            virtual JObject* lastElement();

            virtual void setElementAt(JObject* obj, jint index);

            virtual void removeElementAt(jint index);

            virtual void insertElementAt(JObject* obj, jint index);

            virtual void addElement(JObject* obj);

            virtual bool removeElement(JObject* obj);

            virtual void removeAllElements();

            virtual JPrimitiveObjectArray* toArray();

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a);

            virtual JVector* clone();

            virtual JObject* get(jint index);

            virtual JObject* set(jint index, JObject* element);

            virtual jbool add(JObject* item);

            virtual jbool remove(JObject* e);

            virtual void add(jint index,JObject* item);

            virtual JObject* remove(jint index);

            virtual void clear();

            virtual jbool containsAll(JCollection* c);

            virtual jbool addAll(JCollection* c);

            virtual jbool removeAll(JCollection* c);

            virtual jbool retainAll(JCollection* c);

            virtual jbool addAll(jint index, JCollection* c);

            virtual jbool equals(JObject* other);

            virtual jint hashCode();

            virtual JString* toString();

            virtual JList* subList(jint fromIndex, jint toIndex);

            virtual void removeRange(jint fromIndex, jint toIndex);

            virtual ~JVector();
        };
    }
}

#endif
