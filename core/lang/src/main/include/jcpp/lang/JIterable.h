#ifndef JCPP_LANG_JITERABLE_H
#define JCPP_LANG_JITERABLE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JIterator.h"
#include "jcpp/lang/JObject.h"

using namespace jcpp::util;

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.Iterable", simpleName="Iterable");
        class JCPP_EXPORT JIterable : public JInterface{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual JIterator* iterator()=0;

            virtual ~JIterable();
        };
    }
}

#endif
