#ifndef JCPP_LANG_JVOID_H
#define JCPP_LANG_JVOID_H

#include "jcpp/lang/JObject.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.Void", simpleName="Void");
        class JCPP_EXPORT JVoid : public JObject{
            public:
                static jcpp::lang::JClass* getClazz();

                static jcpp::lang::JClass* TYPE;

                virtual ~JVoid();
        };
    }
}
#endif
