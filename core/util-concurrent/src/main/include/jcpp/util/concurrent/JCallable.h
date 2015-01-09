#ifndef JCPP_UTIL_CONCURRENT_JCALLABLE_H
#define JCPP_UTIL_CONCURRENT_JCALLABLE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.Callable", simpleName="Callable");
            class JCPP_EXPORT JCallable : public JInterface{

            public:
                static JClass* getClazz();

                virtual JObject* call()=0;

                virtual ~JCallable();
            };

        }
    }
}

#endif
