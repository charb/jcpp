#ifndef JCPP_UTIL_JLISTITERATOR_H
#define JCPP_UTIL_JLISTITERATOR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/util/JIterator.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.ListIterator", simpleName="ListIterator");
        class JCPP_EXPORT JListIterator : public JIterator{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual jbool hasNext()=0;

            virtual JObject* next()=0;

            virtual jbool hasPrevious()=0;

            virtual JObject* previous()=0;

            virtual jint nextIndex()=0;

            virtual jint previousIndex()=0;

            virtual void remove()=0;

            virtual void set(JObject*)=0;

            virtual void add(JObject*)=0;

            virtual ~JListIterator();
        };
    }
}

#endif
