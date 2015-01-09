#ifndef JCPP_UTIL_CONCURRENT_JEXECUTORSERVICE_H
#define JCPP_UTIL_CONCURRENT_JEXECUTORSERVICE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/concurrent/JExecutor.h"
#include "jcpp/util/concurrent/JFuture.h"
#include "jcpp/util/concurrent/JCallable.h"
#include "jcpp/lang/JRunnable.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.ExecutorService", simpleName="ExecutorService");
            class JCPP_EXPORT JExecutorService : public JExecutor{
            public:
                static JClass* getClazz();

                virtual void shutdown()=0;

                virtual jbool isShutdown()=0;

                virtual jbool isTerminated()=0;

                virtual jbool awaitTermination(jlong timeout)=0;

                virtual JFuture* submit(JCallable* task)=0;

                virtual JFuture* submit(JRunnable* task,JObject* result)=0;

                virtual JFuture* submit(JRunnable* task)=0;

                virtual ~JExecutorService();
            };
        }
    }
}

#endif
