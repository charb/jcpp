#ifndef JCPP_UTIL_CONCURRENT_JCOMPLETION_SERVICE_H
#define JCPP_UTIL_CONCURRENT_JCOMPLETION_SERVICE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/util/concurrent/JFuture.h"
#include "jcpp/util/concurrent/JCallable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.CompletionService", simpleName="CompletionService");
            class JCPP_EXPORT JCompletionService : public JInterface{
            public:
                static JClass* getClazz();

                virtual JFuture* submit(JCallable* task)=0;

                virtual JFuture* submit(JRunnable* task, JObject* result)=0;

                virtual JFuture* take()=0;

                virtual JFuture* poll()=0;

                virtual JFuture* poll(jlong timeout)=0;

                virtual ~JCompletionService();
            };
        }
    }
}

#endif
