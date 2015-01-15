#ifndef JCPP_UTIL_JABSTRACTLIST_H
#define JCPP_UTIL_JABSTRACTLIST_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JAbstractCollection.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JListIterator.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
    	class JItr;
    	class JListIteratorImpl;
    	class JListItr;
    	class JSubList;
    	class JArrayListItr;
    	class JArrayListListItr;
    	class JArrayListSubList;
    	class JArrayListSubListIterator;

    	// @Class(canonicalName="java.util.AbstractList", simpleName="AbstractList");
        class JCPP_EXPORT JAbstractList : public JAbstractCollection, public virtual JList{
        private:
        	// @IgnoreReflection()
        	JAbstractList(const JAbstractList& list);
        protected:
            jint modCount;
            JAbstractList(jcpp::lang::JClass* _class);
            friend class JItr;
            friend class JListIteratorImpl;
            friend class JListItr;
            friend class JSubList;
            friend class JArrayListItr;
            friend class JArrayListListItr;
            friend class JArrayListSubList;
            friend class JArrayListSubListIterator;

        public:
            static jcpp::lang::JClass* getClazz();
            
            virtual jint size()=0;

            virtual jbool isEmpty();

            virtual jbool add(JObject* e);

            virtual JObject* set(jint index, JObject* element);

            virtual void add(jint index, JObject* element);

            virtual jbool remove(JObject* o);

            virtual JObject* remove(jint jindex);

            virtual jbool contains(JObject* o);

            virtual jbool containsAll(JCollection* c);

            virtual jbool removeAll(JCollection* c);

            virtual jbool retainAll(JCollection* c);

            virtual jint indexOf(JObject* o);

            virtual jint lastIndexOf(JObject* o);

            virtual void clear();

            virtual jbool addAll(JCollection* c);

            virtual jbool addAll(jint index, JCollection* c);

            virtual JPrimitiveObjectArray* toArray();

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a);

            virtual JIterator* iterator();

            virtual JListIterator* listIterator();

            virtual JListIterator* listIterator(jint index);

            virtual JList* subList(jint fromIndex, jint toIndex);

            virtual jbool equals(JObject* o);

            virtual jint hashCode();

            virtual void removeRange(jint fromIndex, jint toIndex);

            virtual ~JAbstractList();
        };
    }
}

#endif
