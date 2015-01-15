#ifndef JCPP_UTIL_JRANDOMACCESS_H
#define JCPP_UTIL_JRANDOMACCESS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.RandomAccess", simpleName="RandomAccess");
        class JCPP_EXPORT JRandomAccess : public JInterface{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual ~JRandomAccess();
        };
    }
}
#endif
