#ifndef JCPP_UTIL_JARRAYLIST_H
#define JCPP_UTIL_JARRAYLIST_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JAbstractList.h"
#include "jcpp/util/JRandomAccess.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveInt.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JObjectInputStream;
        class JObjectOutputStream;
    }
    namespace util{
    	class JArrayListClass;
    	class JArrayListSubList;

    	// @Class(canonicalName="java.util.ArrayList", simpleName="ArrayList");
        class JCPP_EXPORT JArrayList : public JAbstractList, public JRandomAccess, public JCloneable, public JSerializable{
        private:
        	static const jlong serialVersionUID = 8683452581122892189LL;

        protected:
            JPrimitiveObjectArray* items;
            JPrimitiveInt* isize;
            static jint MAX_ARRAY_SIZE;

            virtual void ensureExplicitCapacity(jint c);
            virtual void grow(jint c);
            virtual jint hugeCapacity(jint c);
            virtual void fastRemove(jint index);
            virtual jbool batchRemove(JCollection* c, jbool complement);
            virtual void rangeCheck(jint index);
            virtual void rangeCheckForAdd(jint index);
            virtual void removeRange(jint fromIndex, jint toIndex);
            virtual void writeObject(jcpp::io::JObjectOutputStream* out);
            virtual void readObject(jcpp::io::JObjectInputStream* in);
            friend class JArrayListClass;
            friend class JArrayListSubList;

        public:
            JArrayList(jint initialCapacity = 10);
            
            JArrayList(JCollection* c);

            static jcpp::lang::JClass* getClazz();

            virtual void trimToSize();

            virtual void ensureCapacity(jint minCapacity);

            virtual jint size();

            virtual jbool isEmpty();

            virtual jbool contains(JObject* o);

            virtual jint indexOf(JObject* o);

            virtual jint lastIndexOf(JObject* o);

            virtual JArrayList* clone();

            virtual JPrimitiveObjectArray* toArray();

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a);

            virtual JObject* get(jint index);

            virtual JObject* set(jint index, JObject* element);

            virtual jbool add(JObject* item);

            virtual void add(jint index,JObject* item);

            virtual JObject* remove(jint index);

            virtual jbool remove(JObject* e);

            virtual jbool removeAll(JCollection* c);

            virtual jbool retainAll(JCollection* c);

            virtual void clear();

            virtual jbool addAll(JCollection* c);

            virtual jbool addAll(jint index, JCollection* c);

            virtual JListIterator* listIterator();

            virtual JIterator* iterator();

            virtual JList* subList(jint fromIndex, jint toIndex);

            virtual ~JArrayList();
        };
    }
}

#endif
