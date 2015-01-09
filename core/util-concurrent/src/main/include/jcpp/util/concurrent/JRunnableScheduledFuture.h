#ifndef JCPP_UTIL_CONCURRENT_JRUNNABLESCHEDULEDFUTURE_H
#define JCPP_UTIL_CONCURRENT_JRUNNABLESCHEDULEDFUTURE_H

#include "jcpp/lang/JClass.h"
#include "jcpp/util/concurrent/JRunnableFuture.h"
#include "jcpp/util/concurrent/JScheduledFuture.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.RunnableScheduledFuture", simpleName="RunnableScheduledFuture");
            class JCPP_EXPORT JRunnableScheduledFuture : public virtual JRunnableFuture, public virtual JScheduledFuture{
            public:
                static JClass* getClazz();

                virtual jbool isPeriodic()=0;

                virtual ~JRunnableScheduledFuture();
            };
        }
    }
}

#endif
