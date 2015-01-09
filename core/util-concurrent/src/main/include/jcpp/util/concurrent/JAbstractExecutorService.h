#ifndef JCPP_UTIL_CONCURRENT_JABSTRACTEXECUTORSERVICE_H
#define JCPP_UTIL_CONCURRENT_JABSTRACTEXECUTORSERVICE_H

#include "jcpp/lang/JClass.h"
#include "jcpp/util/concurrent/JFuture.h"
#include "jcpp/util/concurrent/JCallable.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/util/concurrent/JRunnableFuture.h"
#include "jcpp/util/concurrent/JExecutorService.h"
#include "jcpp/util/concurrent/JFutureTask.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.AbstractExecutorService", simpleName="AbstractExecutorService");
            class JCPP_EXPORT JAbstractExecutorService : public JExecutorService, public JObject{
            protected:
                JAbstractExecutorService(JClass* _class);
                JRunnableFuture* newTaskFor(JRunnable* runnable, JObject* result);
                JRunnableFuture* newTaskFor(JCallable* callable);

            public:
                static JClass* getClazz();

                virtual JFuture* submit(JRunnable* task);

                virtual JFuture* submit(JRunnable* task, JObject* result);

                virtual JFuture* submit(JCallable* task);

                virtual ~JAbstractExecutorService();
            };
        }
    }
}

#endif
