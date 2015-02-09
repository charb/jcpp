#ifndef JCPP_UTIL_JABSTRACT_SEQUENTIAL_LIST_H
#define JCPP_UTIL_JABSTRACT_SEQUENTIAL_LIST_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JAbstractList.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JListIterator.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.AbstractSequentialList", simpleName="AbstractSequentialList");
        class JCPP_EXPORT JAbstractSequentialList : public JAbstractList{
        protected:
            JAbstractSequentialList(jcpp::lang::JClass* _class);

        public:
            static jcpp::lang::JClass* getClazz();
            
            virtual JObject* get(jint index);

            virtual JObject* set(jint index,JObject* element);

            virtual void add(jint index, JObject* element);

            virtual JObject* remove(jint index);

            virtual jbool addAll(jint index, JCollection* c);

            virtual JIterator* iterator();

            virtual JListIterator* listIterator(jint index)=0;

            virtual ~JAbstractSequentialList();
        };
    }
}

#endif
