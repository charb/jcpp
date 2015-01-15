#ifndef JCPP_UTIL_JABSTRACTSET_H
#define JCPP_UTIL_JABSTRACTSET_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JAbstractCollection.h"
#include "jcpp/util/JSet.h"
#include "jcpp/util/JListIterator.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.AbstractSet", simpleName="AbstractSet");
        class JCPP_EXPORT JAbstractSet : public JAbstractCollection, public JSet{
        protected:
            JAbstractSet(jcpp::lang::JClass* _class);

        public:
            static jcpp::lang::JClass* getClazz();

            virtual JPrimitiveObjectArray* toArray();

            virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a);

            virtual jint size()=0;

            virtual jbool isEmpty();

            virtual jbool contains(JObject* o);

            virtual JIterator* iterator()=0;

            virtual jbool add(JObject* e);

            virtual jbool remove(JObject* o);

            virtual jbool containsAll(JCollection* c);

            virtual jbool addAll(JCollection* c);

            virtual jbool retainAll(JCollection* c);

            virtual jbool removeAll(JCollection* c);

            virtual void clear();

            virtual jbool equals(JObject* o);

            virtual jint hashCode();

            virtual ~JAbstractSet();
        };
    }
}


#endif
