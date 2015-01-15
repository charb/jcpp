#ifndef JCPP_UTIL_JENUMERATION_H
#define JCPP_UTIL_JENUMERATION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.Enumeration", simpleName="Enumeration");
        class JCPP_EXPORT JEnumeration : public JInterface{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual jbool hasMoreElements()=0;

            virtual JObject* nextElement()=0;

            virtual ~JEnumeration();
        };
    }
}


#endif
