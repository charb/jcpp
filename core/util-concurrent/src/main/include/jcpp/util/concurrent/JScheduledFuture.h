#ifndef JCPP_UTIL_CONCURRENT_JSCHEDULEDFUTURE_H
#define JCPP_UTIL_CONCURRENT_JSCHEDULEDFUTURE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/concurrent/JFuture.h"
#include "jcpp/util/concurrent/JDelayed.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.ScheduledFuture", simpleName="ScheduledFuture");
            class JCPP_EXPORT JScheduledFuture : public virtual JFuture, public virtual JDelayed{
            public:
                static JClass* getClazz();

                virtual ~JScheduledFuture();
            };
        }
    }
}


#endif
