#ifndef JCPP_UTIL_CONCURRENT_JSCHEDULEDEXECUTORSERVICE_H
#define JCPP_UTIL_CONCURRENT_JSCHEDULEDEXECUTORSERVICE_H

#include "jcpp/util/concurrent/JFuture.h"
#include "jcpp/util/concurrent/JCallable.h"
#include "jcpp/util/concurrent/JExecutorService.h"
#include "jcpp/util/concurrent/JScheduledFuture.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.ScheduledExecutorService", simpleName="ScheduledExecutorService");
            class JCPP_EXPORT JScheduledExecutorService : public JExecutorService{
            public:
                static JClass* getClazz();

                virtual JScheduledFuture* schedule(JCallable* callable, jlong delay)=0;

                virtual JScheduledFuture* schedule(JRunnable* command, jlong delay)=0;

                virtual JScheduledFuture* scheduleAtFixedRate(JRunnable* command, jlong initialDelay, jlong period)=0;

                virtual JScheduledFuture* scheduleWithFixedDelay(JRunnable* callable, jlong initialDelay, jlong delay)=0;

                virtual ~JScheduledExecutorService();
            };
        }
    }
}


#endif
