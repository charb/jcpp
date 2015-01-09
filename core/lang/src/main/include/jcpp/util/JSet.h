#ifndef JCPP_UITL_JSET_H
#define JCPP_UITL_JSET_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JIterator.h"
#include "jcpp/util/JListIterator.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JSet : public virtual JCollection{
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

            virtual jbool retainAll(JCollection* c)=0;

            virtual jbool removeAll(JCollection* c)=0;

            virtual void clear()=0;

            virtual jbool equals(JObject* o)=0;

            virtual jint hashCode()=0;

            virtual ~JSet();
        };
    }
}
#endif
