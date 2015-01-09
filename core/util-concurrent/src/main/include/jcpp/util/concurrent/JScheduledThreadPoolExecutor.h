#ifndef JCPP_UTIL_CONCURRENT_JSCHEDULED_THREADPOOLEXECUTOR_H
#define JCPP_UTIL_CONCURRENT_JSCHEDULED_THREADPOOLEXECUTOR_H

#include "jcpp/lang/JClass.h"
#include "jcpp/util/JHashSet.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/concurrent/JFuture.h"
#include "jcpp/util/concurrent/JCallable.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/util/concurrent/JExecutorService.h"
#include "jcpp/util/concurrent/JThreadFactory.h"
#include "jcpp/util/concurrent/JRejectedExecutionHandler.h"
#include "jcpp/util/concurrent/JAbstractExecutorService.h"
#include "jcpp/util/concurrent/JBlockingQueue.h"
#include "jcpp/util/concurrent/atomic/JAtomicLong.h"
#include "jcpp/util/concurrent/locks/JReentrantLock.h"
#include "jcpp/util/concurrent/locks/JCondition.h"
#include "jcpp/util/concurrent/JScheduledExecutorService.h"
#include "jcpp/util/concurrent/JRunnableScheduledFuture.h"
#include "jcpp/util/concurrent/JThreadPoolExecutor.h"

using namespace jcpp::util::concurrent::atomic;
using namespace jcpp::util::concurrent::locks;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.ScheduledThreadPoolExecutor", simpleName="ScheduledThreadPoolExecutor");
            class JCPP_EXPORT JScheduledThreadPoolExecutor : public JThreadPoolExecutor, public JScheduledExecutorService{
            protected:
                jbool continueExistingPeriodicTasksAfterShutdown;
                jbool executeExistingDelayedTasksAfterShutdown;     
                jbool removeOnCancel;
                static JAtomicLong* sequencer;
                virtual jlong now();
                virtual jbool canRunInCurrentRunState(jbool periodic);
                virtual void delayedExecute(JRunnableScheduledFuture* task);
                virtual void reExecutePeriodic(JRunnableScheduledFuture* task);
                virtual void onShutdown();
                virtual JRunnableScheduledFuture* decorateTask(JRunnable* runnable, JRunnableScheduledFuture* task);
                virtual JRunnableScheduledFuture* decorateTask(JCallable* callable, JRunnableScheduledFuture* task);
                virtual jlong triggerTime(jlong delay);
                virtual jlong overflowFree(jlong delay);
                friend class JScheduledFutureTask;

            public:
                JScheduledThreadPoolExecutor(jint corePoolSize);

                JScheduledThreadPoolExecutor(jint corePoolSize,JThreadFactory* threadFactory);

                JScheduledThreadPoolExecutor(jint corePoolSize,JRejectedExecutionHandler* handler);

                JScheduledThreadPoolExecutor(jint corePoolSize,JThreadFactory* threadFactory,JRejectedExecutionHandler* handler);

                static JClass* getClazz();

                virtual jbool isShutdown();

                virtual jbool isTerminated();

                virtual jbool awaitTermination(jlong timeout);

                virtual JScheduledFuture* schedule(JRunnable* command,jlong delay);

                virtual JScheduledFuture* schedule(JCallable* callable,jlong delay);

                virtual JScheduledFuture* scheduleAtFixedRate(JRunnable* command,jlong initialDelay,jlong period);

                virtual JScheduledFuture* scheduleWithFixedDelay(JRunnable* command,jlong initialDelay,jlong delay);

                virtual void execute(JRunnable* command);

                virtual JFuture* submit(JRunnable* task);

                virtual JFuture* submit(JRunnable* task, JObject* result);

                virtual JFuture* submit(JCallable* task);

                virtual void setContinueExistingPeriodicTasksAfterShutdownPolicy(jbool value);

                virtual jbool getContinueExistingPeriodicTasksAfterShutdownPolicy();

                virtual void setExecuteExistingDelayedTasksAfterShutdownPolicy(jbool value);

                virtual jbool getExecuteExistingDelayedTasksAfterShutdownPolicy();

                virtual void setRemoveOnCancelPolicy(jbool value);

                virtual jbool getRemoveOnCancelPolicy();

                virtual void shutdown();

                virtual JList* shutdownNow();

                virtual JBlockingQueue* getQueue();

                virtual ~JScheduledThreadPoolExecutor();
            };
        }
    }
}

#endif
