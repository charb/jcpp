#ifndef JCPP_UTIL_CONCURRENT_JRUNNABLEFUTURE_H
#define JCPP_UTIL_CONCURRENT_JRUNNABLEFUTURE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/util/concurrent/JFuture.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.RunnableFuture", simpleName="RunnableFuture");
            class JCPP_EXPORT JRunnableFuture : public virtual JRunnable, public virtual JFuture{
            public:
                static JClass* getClazz();
                
                virtual ~JRunnableFuture();
            };
        }
    }
}

#endif
