#ifndef JCPP_UTIL_CONCURRENT_JFUTURETASK_H
#define JCPP_UTIL_CONCURRENT_JFUTURETASK_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/util/concurrent/JRunnableFuture.h"
#include "jcpp/util/concurrent/JCallable.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/util/concurrent/atomic/JAtomicInteger.h"

using namespace jcpp::util::concurrent::atomic;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.FutureTask", simpleName="FutureTask");
            class JCPP_EXPORT JFutureTask : public virtual JRunnableFuture, public JObject{
            protected:
                static jint NEW;
                static jint COMPLETING;
                static jint NORMAL;
                static jint EXCEPTIONAL;
                static jint CANCELLED;
                static jint INTERRUPTING;
                static jint INTERRUPTED;
                JAtomicInteger* state;
                JCallable* callable;
                JObject* outcome;
                JFutureTask(JClass* _class,JCallable* c);
                JFutureTask(JClass* _class,JRunnable* r,JObject* result);
                virtual JObject* report(jint s);
                virtual void done();
                virtual void set(JObject* o);
                virtual void setException(JThrowable* th);
                virtual jbool runAndReset();
                virtual void finishCompletion();
                virtual jint awaitDone(jbool timed, jlong t);

            public:
                JFutureTask(JCallable* c);

                JFutureTask(JRunnable* r,JObject* result);

                static JClass* getClazz();
                
                virtual jbool isCancelled();

                virtual jbool isDone();

                virtual jbool cancel();

                virtual JObject* get();

                virtual JObject* get(jlong l);

                virtual void run();

                virtual ~JFutureTask();
            };
        }
    }
}

#endif
