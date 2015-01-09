#ifndef JCPP_UTIL_JLIST_H
#define JCPP_UTIL_JLIST_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JIterator.h"
#include "jcpp/util/JListIterator.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace std;

namespace jcpp{
    namespace util{


        class JCPP_EXPORT JList : public JCollection{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual jint size()=0;

            virtual jbool isEmpty()=0;

            virtual jbool contains(JObject* o)=0;

            virtual JIterator* iterator()=0;

            virtual JPrimitiveObjectArray* toArray()=0;

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a)=0;

            virtual jbool add(JObject* e)=0;

            virtual jbool remove(JObject* o)=0;

            virtual jbool containsAll(JCollection* c)=0;

            virtual jbool addAll(JCollection* c)=0;

            virtual jbool addAll(jint index, JCollection* c)=0;

            virtual jbool removeAll(JCollection* c)=0;

            virtual jbool retainAll(JCollection* c)=0;

            virtual void clear()=0;

            virtual jbool equals(JObject* o)=0;

            virtual jint hashCode()=0;

            virtual JObject* get(jint index)=0;

            virtual JObject* set(jint index, JObject* element)=0;

            virtual void add(jint index, JObject* element)=0;

            virtual JObject* remove(jint index)=0;

            virtual jint indexOf(JObject* o)=0;

            virtual jint lastIndexOf(JObject* o)=0;

            virtual JListIterator* listIterator()=0;

            virtual JListIterator* listIterator(jint index)=0;

            virtual JList* subList(jint fromIndex, jint toIndex)=0;

            virtual ~JList();
        };
    }
}

#endif
