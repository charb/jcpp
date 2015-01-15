#ifndef JCPP_UTIL_JITERATOR_H
#define JCPP_UTIL_JITERATOR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.Iterator", simpleName="Iterator");
        class JCPP_EXPORT JIterator : public JInterface{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual jbool hasNext()=0;

            virtual JObject* next()=0;

            virtual void remove()=0;

            virtual ~JIterator();
        };
    }
}

#endif
