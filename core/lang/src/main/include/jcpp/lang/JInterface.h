#ifndef JCPP_LANG_JINTERFACE_H
#define JCPP_LANG_JINTERFACE_H

#include "jcpp/native/api/NativeInclude.h"

namespace jcpp{
    namespace lang{
        class JClass;

        // @Class(canonicalName="java.lang.Interface", simpleName="Interface");
        class JCPP_EXPORT JInterface{
            public:
                static jcpp::lang::JClass* getClazz();
                
                virtual ~JInterface();
        };
    }
}

#endif
