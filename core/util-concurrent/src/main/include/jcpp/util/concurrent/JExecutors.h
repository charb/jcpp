#ifndef JCPP_UTIL_CONCURRENT_JEXECUTORS_H
#define JCPP_UTIL_CONCURRENT_JEXECUTORS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/util/concurrent/JCallable.h"
#include "jcpp/util/concurrent/JThreadFactory.h"
#include "jcpp/util/concurrent/JExecutorService.h"
#include "jcpp/util/concurrent/JScheduledExecutorService.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.Executors", simpleName="Executors");
            class JCPP_EXPORT JExecutors : public JObject{
            public:
                static JClass* getClazz();

                static JCallable* callable(JRunnable* r,JObject* result);

                static JThreadFactory* defaultThreadFactory();

                static JExecutorService* newCachedThreadPool();

                static JExecutorService* newCachedThreadPool(JThreadFactory* threadFactory);

                static JScheduledExecutorService* newScheduledThreadPool(jint corePoolSize);

                virtual ~JExecutors();
            };
        }
    }
}

#endif
