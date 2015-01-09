#ifndef JCPP_UTIL_CONCURRENT_JTHREADPOOLEXECUTOR_H
#define JCPP_UTIL_CONCURRENT_JTHREADPOOLEXECUTOR_H

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
#include "jcpp/util/concurrent/atomic/JAtomicInteger.h"
#include "jcpp/util/concurrent/locks/JReentrantLock.h"
#include "jcpp/util/concurrent/locks/JCondition.h"

using namespace jcpp::util::concurrent::atomic;
using namespace jcpp::util::concurrent::locks;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JWorker;

            // @Class(canonicalName="java.util.concurrent.ThreadPoolExecutor", simpleName="ThreadPoolExecutor");
            class JCPP_EXPORT JThreadPoolExecutor : public JAbstractExecutorService{
            protected:
                static jint COUNT_BITS;
                static jint CAPACITY;
                static jint RUNNING;
                static jint SHUTDOWN;
                static jint STOP;
                static jint TIDYING;
                static jint TERMINATED;
                static jbool ONLY_ONE;
                static JRejectedExecutionHandler* defaultHandler;
                static jint runStateOf(jint c);
                static jint workerCountOf(jint c);
                static jint ctlOf(jint rs,jint wc);
                static jbool runStateLessThan(jint c,jint s);
                static jbool runStateAtLeast(jint c,jint s);
                static jbool isRunning(jint c);
                JAtomicInteger* ctl;
                JBlockingQueue* workQueue;
                JReentrantLock* mainLock;
                JHashSet* workers;
                JCondition* termination;
                jint largestPoolSize;
                jlong completedTaskCount;
                JThreadFactory* threadFactory;
                JRejectedExecutionHandler* handler;
                jlong keepAliveTime;
                jbool ballowCoreThreadTimeOut;
                jint corePoolSize;
                jint maximumPoolSize;
                JThreadPoolExecutor(JClass* _class,jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue);
                JThreadPoolExecutor(JClass* _class,jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory);
                JThreadPoolExecutor(JClass* _class,jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JRejectedExecutionHandler* handler);
                JThreadPoolExecutor(JClass* _class,jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory,JRejectedExecutionHandler* handler);
                virtual void init(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory,JRejectedExecutionHandler* handler);
                virtual jbool compareAndIncrementWorkerCount(jint expect);
                virtual jbool compareAndDecrementWorkerCount(jint expect);
                virtual void decrementWorkerCount();
                virtual void advanceRunState(jint targetState);
                virtual void tryTerminate();
                virtual void interruptWorkers();
                virtual void interruptIdleWorkers(jbool onlyOne);
                virtual void interruptIdleWorkers();
                virtual void reject(JRunnable* command);
                virtual void onShutdown();
                virtual jbool isRunningOrShutdown(jbool shutdownOK);
                virtual JList* drainQueue();
                virtual jbool addWorker(JRunnable* firstTask, jbool core);
                virtual void addWorkerFailed(JWorker* w);
                virtual void processWorkerExit(JWorker* w,jbool completedAbruptly);
                virtual JRunnable* getTask();
                virtual void runWorker(JWorker* w);
                virtual void ensurePrestart();
                virtual void beforeExecute(JThread* t, JRunnable* r);
                virtual void afterExecute(JRunnable* r, JThrowable* t);
                virtual void terminated();
                friend class JWorker;

            public:
                JThreadPoolExecutor(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue);

                JThreadPoolExecutor(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory);

                JThreadPoolExecutor(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JRejectedExecutionHandler* handler);

                JThreadPoolExecutor(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory,JRejectedExecutionHandler* handler);

                static JClass* getClazz();

                virtual void execute(JRunnable* command);

                virtual void shutdown();

                virtual JList* shutdownNow();

                virtual jbool isShutdown();

                virtual jbool isTerminating();

                virtual jbool isTerminated();

                virtual jbool awaitTermination(jlong timeout);

                virtual void finalize();

                virtual void setThreadFactory(JThreadFactory* threadFactory);

                virtual JThreadFactory* getThreadFactory();

                virtual void setRejectedExecutionHandler(JRejectedExecutionHandler* handler);

                virtual JRejectedExecutionHandler* getRejectedExecutionHandler();

                virtual void setCorePoolSize(jint corePoolSize);

                virtual jint getCorePoolSize();

                virtual jbool prestartCoreThread();

                virtual jint prestartAllCoreThreads();

                virtual jbool allowsCoreThreadTimeOut();

                virtual void allowCoreThreadTimeOut(jbool value);

                virtual void setMaximumPoolSize(jint maximumPoolSize);

                virtual jint getMaximumPoolSize();

                virtual void setKeepAliveTime(jlong time);

                virtual jlong getKeepAliveTime();

                virtual JBlockingQueue* getQueue();

                virtual jbool remove(JRunnable* task);

                virtual void purge();

                virtual jint getPoolSize();

                virtual jint getActiveCount();

                virtual jint getLargestPoolSize();

                virtual jlong getTaskCount();

                virtual jlong getCompletedTaskCount();

                virtual JString* toString();

                virtual ~JThreadPoolExecutor();
            };
        }
    }
}

#endif
