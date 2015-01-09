#include "jcpp/util/concurrent/JThreadPoolExecutor.h"
#include "jcpp/util/concurrent/JExecutors.h"
#include "jcpp/util/concurrent/JRejectedExecutionException.h"
#include "jcpp/util/JQueue.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/util/JHashSet.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/lang/JError.h"
#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JIllegalThreadStateException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JInstantiationException.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

            jint JThreadPoolExecutor::COUNT_BITS = JInteger::SIZE - 3;
            jint JThreadPoolExecutor::CAPACITY   = (1 << JThreadPoolExecutor::COUNT_BITS) - 1;
            jint JThreadPoolExecutor::RUNNING    = -1 << JThreadPoolExecutor::COUNT_BITS;
            jint JThreadPoolExecutor::SHUTDOWN   =  0 << JThreadPoolExecutor::COUNT_BITS;
            jint JThreadPoolExecutor::STOP       =  1 << JThreadPoolExecutor::COUNT_BITS;
            jint JThreadPoolExecutor::TIDYING    =  2 << JThreadPoolExecutor::COUNT_BITS;
            jint JThreadPoolExecutor::TERMINATED =  3 << JThreadPoolExecutor::COUNT_BITS;
            jbool JThreadPoolExecutor::ONLY_ONE = true;

            jint JThreadPoolExecutor::runStateOf(jint c){ 
                return c & ~CAPACITY; 
            }
    
            jint JThreadPoolExecutor::workerCountOf(jint c)  { 
                return c & CAPACITY; 
            }
    
            jint JThreadPoolExecutor::ctlOf(jint rs, jint wc) { 
                return rs | wc; 
            }

            jbool JThreadPoolExecutor::runStateLessThan(jint c, jint s) {
                return c < s;
            }

            jbool JThreadPoolExecutor::runStateAtLeast(jint c, jint s) {
                return c >= s;
            }

            jbool JThreadPoolExecutor::isRunning(jint c) {
                return c < SHUTDOWN;
            }

            JThreadPoolExecutor::JThreadPoolExecutor(JClass* _class,jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue) : JAbstractExecutorService(_class) {
                init(corePoolSize, maximumPoolSize, keepAliveTime, workQueue,JExecutors::defaultThreadFactory(), defaultHandler);
            }

            JThreadPoolExecutor::JThreadPoolExecutor(JClass* _class,jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory) : JAbstractExecutorService(_class){
                init(corePoolSize, maximumPoolSize, keepAliveTime, workQueue,threadFactory, defaultHandler);
            }

            JThreadPoolExecutor::JThreadPoolExecutor(JClass* _class,jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JRejectedExecutionHandler* handler) : JAbstractExecutorService(_class){
                init(corePoolSize, maximumPoolSize, keepAliveTime, workQueue,JExecutors::defaultThreadFactory(), handler);
            }

            JThreadPoolExecutor::JThreadPoolExecutor(JClass* _class,jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory,JRejectedExecutionHandler* handler) : JAbstractExecutorService(_class) {
                init(corePoolSize,maximumPoolSize,keepAliveTime,workQueue,threadFactory,handler);
            }

            JThreadPoolExecutor::JThreadPoolExecutor(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue) : JAbstractExecutorService(getClazz()) {
                init(corePoolSize, maximumPoolSize, keepAliveTime, workQueue,JExecutors::defaultThreadFactory(), defaultHandler);
            }

            JThreadPoolExecutor::JThreadPoolExecutor(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory) : JAbstractExecutorService(getClazz()){
                init(corePoolSize, maximumPoolSize, keepAliveTime, workQueue,threadFactory, defaultHandler);
            }

            JThreadPoolExecutor::JThreadPoolExecutor(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JRejectedExecutionHandler* handler) : JAbstractExecutorService(getClazz()){
                init(corePoolSize, maximumPoolSize, keepAliveTime, workQueue,JExecutors::defaultThreadFactory(), handler);
            }

            JThreadPoolExecutor::JThreadPoolExecutor(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory,JRejectedExecutionHandler* handler) : JAbstractExecutorService(getClazz()) {
                init(corePoolSize,maximumPoolSize,keepAliveTime,workQueue,threadFactory,handler);
            }

            void JThreadPoolExecutor::init(jint corePoolSize,jint maximumPoolSize,jlong keepAliveTime,JBlockingQueue* workQueue,JThreadFactory* threadFactory,JRejectedExecutionHandler* handler) {
                if (corePoolSize < 0 || maximumPoolSize <= 0 || maximumPoolSize < corePoolSize || keepAliveTime < 0){
                    throw new JIllegalArgumentException();
                }
                if (workQueue == null || threadFactory == null || handler == null){
                    throw new JNullPointerException();
                }
                this->corePoolSize = corePoolSize;
                this->maximumPoolSize = maximumPoolSize;
                this->workQueue = workQueue;
                this->keepAliveTime = keepAliveTime;
                this->threadFactory = threadFactory;
                this->handler = handler;
                ctl = new JAtomicInteger(ctlOf(RUNNING, 0));
                mainLock = new JReentrantLock();
                workers = new JHashSet();
                termination = mainLock->newCondition();
                largestPoolSize=0;
                completedTaskCount=0;
                ballowCoreThreadTimeOut=false;
            }

            // @Class(canonicalName="java.util.concurrent.ThreadPoolExecutor$Worker", simpleName="ThreadPoolExecutor$Worker");
            class JWorker : public JObject, public JRunnable{
            protected:
                JThreadPoolExecutor* threadPoolExecutor;
                JThread* thread;
                JRunnable* firstTask;
                jlong completedTasks;
                JObject* theLock;
                JAtomicInteger* nbLock;
                friend class JThreadPoolExecutor;

            public:
                JWorker(JThreadPoolExecutor* threadPoolExecutor,JRunnable* firstTask) : JObject(getClazz()){
                    this->threadPoolExecutor=threadPoolExecutor;
                    this->firstTask = firstTask;
                    this->thread = threadPoolExecutor->getThreadFactory()->newThread(this);
                    theLock=new JObject();
                    nbLock=new JAtomicInteger();
                    completedTasks=0;
                }

                static JClass* getClazz();

                virtual void run() {
                    threadPoolExecutor->runWorker(this);
                }

                void lock(){ 
                    theLock->internalLock();
                    nbLock->incrementAndGet();
                }
                
                jbool tryLock()  { 
                    jbool b=theLock->internalTryLock(); 
                    if (b){
                        nbLock->incrementAndGet();
                    }
                    return b;
                }
                
                void unlock(){ 
                    theLock->internalUnlock();
                    nbLock->decrementAndGet();
                }
                
                jbool isLocked() { 
                    return nbLock->get()!=0; 
                }
            };

            jbool JThreadPoolExecutor::compareAndIncrementWorkerCount(jint expect) {
                return ctl->compareAndSet(expect, expect + 1);
            }

            jbool JThreadPoolExecutor::compareAndDecrementWorkerCount(jint expect) {
                return ctl->compareAndSet(expect, expect - 1);
            }

            void JThreadPoolExecutor::decrementWorkerCount() {
                do {
                } while (! compareAndDecrementWorkerCount(ctl->get()));
            }

            void JThreadPoolExecutor::advanceRunState(jint targetState) {
                for (;;) {
                    jint c = ctl->get();
                    if (runStateAtLeast(c, targetState) || ctl->compareAndSet(c, ctlOf(targetState, workerCountOf(c)))){
                        break;
                    }
                }
            }

            void JThreadPoolExecutor::tryTerminate() {
                for (;;) {
                    jint c = ctl->get();
                    if (isRunning(c) || runStateAtLeast(c, TIDYING) || (runStateOf(c) == SHUTDOWN && !workQueue->isEmpty())){
                        return;
                    }
                    if (workerCountOf(c) != 0) {
                        interruptIdleWorkers(ONLY_ONE);
                        return;
                    }

                    JReentrantLock* mainLock = this->mainLock;
                    mainLock->lock();
                    try_finally({
                        if (ctl->compareAndSet(c, ctlOf(TIDYING, 0))) {
                            try_finally({
                                terminated();
                            },{
                                ctl->set(ctlOf(TERMINATED, 0));
                                termination->signalAll();
                            })
                        }
                    },{
                        mainLock->unlock();
                    })
                }
            }

            void JThreadPoolExecutor::interruptWorkers() {
            }

            void JThreadPoolExecutor::interruptIdleWorkers(jbool onlyOne){
            }
            
            void JThreadPoolExecutor::interruptIdleWorkers(){
            }

            void JThreadPoolExecutor::reject(JRunnable* command) {
                handler->rejectedExecution(command, this);
            }

            void JThreadPoolExecutor::onShutdown() {
            }

            jbool JThreadPoolExecutor::isRunningOrShutdown(jbool shutdownOK) {
                jint rs = runStateOf(ctl->get());
                return rs == RUNNING || (rs == SHUTDOWN && shutdownOK);
            }

            JList* JThreadPoolExecutor::drainQueue() {
                JBlockingQueue* q = workQueue;
                JArrayList* taskList = new JArrayList();
                q->drainTo(reinterpret_cast<JCollection*>(taskList));
                if (!q->isEmpty()) {
                    JPrimitiveObjectArray* a=q->toArray();
                    for (jint i=0;i<a->size();i++){
                        JRunnable* r=dynamic_cast<JRunnable*>(a->get(i));
                        if (q->remove(dynamic_cast<JObject*>(r))){
                            taskList->add(dynamic_cast<JObject*>(r));
                        }
                    }
                }
                return taskList;
            }

            jbool JThreadPoolExecutor::addWorker(JRunnable* firstTask, jbool core) {
                for (;;) {
                    jint c = ctl->get();
                    jint rs = runStateOf(c);

                    if (rs >= SHUTDOWN && ! (rs == SHUTDOWN && firstTask == null && !workQueue->isEmpty())){
                        return false;
                    }

                    jbool doEnd=false;
                    for (;;) {
                        jint wc = workerCountOf(c);
                        if (wc >= CAPACITY || wc >= (core ? corePoolSize : maximumPoolSize)){
                            return false;
                        }
                        if (compareAndIncrementWorkerCount(c)){
                            doEnd=true;
                            break;
                        }
                        c = ctl->get();
                        if (runStateOf(c) != rs){
                            continue;
                        }
                    }
                    if (doEnd){
                        break;
                    }
                }

                jbool workerStarted = false;
                jbool workerAdded = false;
                JWorker* w = null;
                try_finally({
                    w = new JWorker(this,firstTask);
                    JThread* t = w->thread;
                    if (t != null) {
                        JReentrantLock* mainLock = this->mainLock;
                        mainLock->lock();
                        try_finally({
                            jint rs = runStateOf(ctl->get());
                            if (rs < SHUTDOWN || (rs == SHUTDOWN && firstTask == null)) {
                                if (t->isAlive()){
                                    throw new JIllegalThreadStateException();
                                }
                                workers->add(w);
                                jint s = workers->size();
                                if (s > largestPoolSize){
                                    largestPoolSize = s;
                                }
                                workerAdded = true;
                            }
                        },{
                            mainLock->unlock();
                        })
                        if (workerAdded) {
                            t->start();
                            workerStarted = true;
                        }
                    }
                },{
                    if (! workerStarted){
                        addWorkerFailed(w);
                    }
                })
                return workerStarted;
            }

            void JThreadPoolExecutor::addWorkerFailed(JWorker* w) {
                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    if (w != null){
                        workers->remove(w);
                    }
                    decrementWorkerCount();
                    tryTerminate();
                },{
                    mainLock->unlock();
                })
            }

            void JThreadPoolExecutor::processWorkerExit(JWorker* w, jbool completedAbruptly) {
                if (completedAbruptly){
                    decrementWorkerCount();
                }

                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    completedTaskCount += w->completedTasks;
                    workers->remove(w);
                },{
                    mainLock->unlock();
                })

                tryTerminate();

                jint c = ctl->get();
                if (runStateLessThan(c, STOP)) {
                    if (!completedAbruptly) {
                        jint min = ballowCoreThreadTimeOut ? 0 : corePoolSize;
                        if (min == 0 && ! workQueue->isEmpty()){
                            min = 1;
                        }
                        if (workerCountOf(c) >= min){
                            return;
                        }
                    }
                    addWorker(null, false);
                }
            }

            JRunnable* JThreadPoolExecutor::getTask() {
                jbool timedOut = false;

                for (;;) {
                    jint c = ctl->get();
                    jint rs = runStateOf(c);

                    if (rs >= SHUTDOWN && (rs >= STOP || workQueue->isEmpty())) {
                        decrementWorkerCount();
                        return null;
                    }

                    jint wc = workerCountOf(c);
                    jbool timed = ballowCoreThreadTimeOut || wc > corePoolSize;

                    if ((wc > maximumPoolSize || (timed && timedOut)) && (wc > 1 || workQueue->isEmpty())) {
                        if (compareAndDecrementWorkerCount(c)){
                            return null;
                        }
                        continue;
                    }
                    JRunnable* r = timed ? dynamic_cast<JRunnable*>(workQueue->poll(keepAliveTime)) : dynamic_cast<JRunnable*>(workQueue->take());
                    if (r != null){
                        return r;
                    }
                    timedOut = true;
                }
            }

            void JThreadPoolExecutor::runWorker(JWorker* w) {
                JThread* wt = JThread::currentThread();
                JRunnable* task = w->firstTask;
                w->firstTask = null;
                w->unlock();
                jbool completedAbruptly = true;
                try_finally({
                    while (task != null || (task = getTask()) != null) {
                        w->lock();
                        try_finally({
                            beforeExecute(wt, task);
                            JThrowable* thrown = null;
                            try{
                                task->run();
                                afterExecute(task, thrown);
                            }catch(JThrowable* th){
                                thrown=th;
                                afterExecute(task, thrown);
                            }
                        }, {
                            task = null;
                            w->completedTasks++;
                            w->unlock();
                        })
                    }
                    completedAbruptly = false;
                },{
                    processWorkerExit(w, completedAbruptly);
                })
            }

            void JThreadPoolExecutor::execute(JRunnable* command) {
                if (command == null){
                    throw new JNullPointerException();
                }
                jint c = ctl->get();
                if (workerCountOf(c) < corePoolSize) {
                    if (addWorker(command, true)){
                        return;
                    }
                    c = ctl->get();
                }
                if (isRunning(c) && workQueue->offer(dynamic_cast<JObject*>(command))) {
                    jint recheck = ctl->get();
                    if (! isRunning(recheck) && remove(command)) {
                        reject(command);
                    }else if (workerCountOf(recheck) == 0){
                        addWorker(null, false);
                    }
                }else if (!addWorker(command, false)){
                    reject(command);
                }
            }

            void JThreadPoolExecutor::shutdown() {
                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    advanceRunState(SHUTDOWN);
                    interruptIdleWorkers();
                    onShutdown();
                },{
                    mainLock->unlock();
                })
                tryTerminate();
            }

            JList* JThreadPoolExecutor::shutdownNow() {
                JList* tasks=null;
                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    advanceRunState(STOP);
                    interruptWorkers();
                    tasks = drainQueue();
                },{
                    mainLock->unlock();
                })
                tryTerminate();
                return tasks;
            }

            jbool JThreadPoolExecutor::isShutdown() {
                return ! isRunning(ctl->get());
            }

            jbool JThreadPoolExecutor::isTerminating() {
                jint c = ctl->get();
                return ! isRunning(c) && runStateLessThan(c, TERMINATED);
            }

            jbool JThreadPoolExecutor::isTerminated() {
                return runStateAtLeast(ctl->get(), TERMINATED);
            }

            jbool JThreadPoolExecutor::awaitTermination(jlong timeout){
                jbool res=false;
                jlong nanos = timeout;
                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    for (;;) {
                        if (runStateAtLeast(ctl->get(), TERMINATED)){
                            res=true;
                            break;
                        }
                        if (nanos <= 0){
                            break;
                        }
                        nanos = termination->await(nanos);
                    }
                }, {
                    mainLock->unlock();
                })
                return res;
            }

            void JThreadPoolExecutor::finalize() {
                shutdown();
            }

            void JThreadPoolExecutor::setThreadFactory(JThreadFactory* threadFactory) {
                if (threadFactory == null){
                    throw new JNullPointerException();
                }
                this->threadFactory = threadFactory;
            }

            JThreadFactory* JThreadPoolExecutor::getThreadFactory() {
                return threadFactory;
            }

            void JThreadPoolExecutor::setRejectedExecutionHandler(JRejectedExecutionHandler* handler) {
                if (handler == null){
                    throw new JNullPointerException();
                }
                this->handler = handler;
            }

            JRejectedExecutionHandler* JThreadPoolExecutor::getRejectedExecutionHandler() {
                return handler;
            }

            void JThreadPoolExecutor::setCorePoolSize(jint corePoolSize) {
                if (corePoolSize < 0){
                    throw new JIllegalArgumentException();
                }
                jint delta = corePoolSize - this->corePoolSize;
                this->corePoolSize = corePoolSize;
                if (workerCountOf(ctl->get()) > corePoolSize){
                    interruptIdleWorkers();
                }else if (delta > 0) {
                    jint k = (delta < workQueue->size() ? delta : workQueue->size());
                    while (k-- > 0 && addWorker(null, true)) {
                        if (workQueue->isEmpty()){
                            break;
                        }
                    }
                }
            }

            jint JThreadPoolExecutor::getCorePoolSize() {
                return corePoolSize;
            }

            jbool JThreadPoolExecutor::prestartCoreThread() {
                return workerCountOf(ctl->get()) < corePoolSize && addWorker(null, true);
            }

            void JThreadPoolExecutor::ensurePrestart() {
                jint wc = workerCountOf(ctl->get());
                if (wc < corePoolSize){
                    addWorker(null, true);
                }else if (wc == 0){
                    addWorker(null, false);
                }
            }

            jint JThreadPoolExecutor::prestartAllCoreThreads() {
                jint n = 0;
                while (addWorker(null, true)){
                    ++n;
                }
                return n;
            }

            jbool JThreadPoolExecutor::allowsCoreThreadTimeOut() {
                return ballowCoreThreadTimeOut;
            }

            void JThreadPoolExecutor::allowCoreThreadTimeOut(jbool value) {
                if (value && keepAliveTime <= 0){
                    throw new JIllegalArgumentException(new JString("Core threads must have nonzero keep alive times"));
                }
                if (value != ballowCoreThreadTimeOut) {
                    ballowCoreThreadTimeOut = value;
                    if (value){
                        interruptIdleWorkers();
                    }
                }
            }

            void JThreadPoolExecutor::setMaximumPoolSize(jint maximumPoolSize) {
                if (maximumPoolSize <= 0 || maximumPoolSize < corePoolSize){
                    throw new JIllegalArgumentException();
                }
                this->maximumPoolSize = maximumPoolSize;
                if (workerCountOf(ctl->get()) > maximumPoolSize){
                    interruptIdleWorkers();
                }
            }

            jint JThreadPoolExecutor::getMaximumPoolSize() {
                return maximumPoolSize;
            }

            void JThreadPoolExecutor::setKeepAliveTime(jlong time) {
                if (time < 0){
                    throw new JIllegalArgumentException();
                }
                if (time == 0 && allowsCoreThreadTimeOut()){
                    throw new JIllegalArgumentException(new JString("Core threads must have nonzero keep alive times"));
                }
                jlong keepAliveTime = time;
                jlong delta = keepAliveTime - this->keepAliveTime;
                this->keepAliveTime = keepAliveTime;
                if (delta < 0){
                    interruptIdleWorkers();
                }
            }

            jlong JThreadPoolExecutor::getKeepAliveTime() {
                return keepAliveTime;
            }

            JBlockingQueue* JThreadPoolExecutor::getQueue() {
                return workQueue;
            }

            jbool JThreadPoolExecutor::remove(JRunnable* task) {
                jbool removed = workQueue->remove(dynamic_cast<JObject*>(task));
                tryTerminate();
                return removed;
            }

            void JThreadPoolExecutor::purge() {
                JBlockingQueue* q = workQueue;
                try {
                    JIterator* it = q->iterator();
                    while (it->hasNext()) {
                        JRunnable* r = dynamic_cast<JRunnable*>(it->next());
                        if (dynamic_cast<JObject*>(r)->isInstanceOf(JFuture::getClazz()) && (dynamic_cast<JFuture*>(r))->isCancelled()){
                            it->remove();
                        }
                    }
                } catch (JConcurrentModificationException* fallThrough) {
                    JPrimitiveObjectArray* a=q->toArray();
                    for (jint i=0;i<a->size();i++){
                        JObject* r = a->get(i);
                        if (dynamic_cast<JObject*>(r)->isInstanceOf(JFuture::getClazz()) && (dynamic_cast<JFuture*>(r))->isCancelled()){
                            q->remove(r);
                        }
                    }
                }
                tryTerminate();
            }

            jint JThreadPoolExecutor::getPoolSize() {
                jint res=0;
                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    res=runStateAtLeast(ctl->get(), TIDYING) ? 0 : workers->size();
                } ,{
                    mainLock->unlock();
                })
                return res;
            }

            jint JThreadPoolExecutor::getActiveCount() {
                jint res=0;
                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    JIterator* iterator=workers->iterator();
                    while (iterator->hasNext()){
                        JWorker* w=dynamic_cast<JWorker*>(iterator->next());
                        if (w->isLocked()){
                            ++res;
                        }
                    }
                }, {
                    mainLock->unlock();
                })
                return res;
            }

            jint JThreadPoolExecutor::getLargestPoolSize() {
                jint res=0;
                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    res=largestPoolSize;
                } ,{
                    mainLock->unlock();
                })
                return res;
            }

            jlong JThreadPoolExecutor::getTaskCount() {
                jlong res=0;
                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    jlong n = completedTaskCount;
                    JIterator* iterator=workers->iterator();
                    while (iterator->hasNext()){
                        JWorker* w=dynamic_cast<JWorker*>(iterator->next());
                        n += w->completedTasks;
                        if (w->isLocked()){
                            ++n;
                        }
                    }
                    res=n + workQueue->size();
                } , {
                    mainLock->unlock();
                })
                return res;
            }

            jlong JThreadPoolExecutor::getCompletedTaskCount() {
                jlong res=0;
                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    jlong n = completedTaskCount;
                    JIterator* iterator=workers->iterator();
                    while (iterator->hasNext()){
                        JWorker* w=dynamic_cast<JWorker*>(iterator->next());
                        n += w->completedTasks;
                    }
                    res=n;
                },{
                    mainLock->unlock();
                })
                return res;
            }

            JString* JThreadPoolExecutor::toString() {
                jlong ncompleted=0;
                jint nworkers=0;
                jint nactive=0;

                JReentrantLock* mainLock = this->mainLock;
                mainLock->lock();
                try_finally({
                    ncompleted = completedTaskCount;
                    nactive = 0;
                    nworkers = workers->size();
                    JIterator* iterator=workers->iterator();
                    while (iterator->hasNext()){
                        JWorker* w=dynamic_cast<JWorker*>(iterator->next());
                        ncompleted += w->completedTasks;
                        if (w->isLocked()){
                            ++nactive;
                        }
                    }
                },{
                    mainLock->unlock();
                })

                jint c = ctl->get();
                JStringBuilder* builder=new JStringBuilder();
                builder->append(JAbstractExecutorService::toString());
                builder->append((runStateLessThan(c, SHUTDOWN) ? "Running" :
                                (runStateAtLeast(c, TERMINATED) ? "Terminated" : "Shutting down")))
                       ->append(", pool size = ")->append(nworkers)
                       ->append(", active threads = ")->append(nactive)
                       ->append(", queued tasks = " )->append(workQueue->size())
                       ->append(", completed tasks = ")->append(ncompleted)
                       ->append("]");
                return builder->toString();
            }

            void JThreadPoolExecutor::beforeExecute(JThread* t, JRunnable* r) { 
            }

            void JThreadPoolExecutor::afterExecute(JRunnable* r, JThrowable* t) { 
            }

            void JThreadPoolExecutor::terminated() { 
            }

            // @Class(canonicalName="java.util.concurrent.ThreadPoolExecutor$CallerRunsPolicy", simpleName="ThreadPoolExecutor$CallerRunsPolicy");
            class JCallerRunsPolicy : public JObject, public JRejectedExecutionHandler {
            public:
                JCallerRunsPolicy() :JObject(getClazz()) { 
                }

                static JClass* getClazz();

                virtual void rejectedExecution(JRunnable* r, JThreadPoolExecutor* e) {
                    if (!e->isShutdown()) {
                        r->run();
                    }
                }
            };

            // @Class(canonicalName="java.util.concurrent.ThreadPoolExecutor$AbortPolicy", simpleName="ThreadPoolExecutor$AbortPolicy");
            class JAbortPolicy : public JObject, public JRejectedExecutionHandler {
            public:
                JAbortPolicy():JObject(getClazz()) {
                }

                static JClass* getClazz();

                virtual void rejectedExecution(JRunnable* r, JThreadPoolExecutor* e) {
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("Task ")->append(dynamic_cast<JObject*>(r)->toString())->append(" rejected from ")->append(e->toString());
                    throw new JRejectedExecutionException(builder->toString());
                }
            };

            // @Class(canonicalName="java.util.concurrent.ThreadPoolExecutor$DiscardPolicy", simpleName="ThreadPoolExecutor$DiscardPolicy");
            class JDiscardPolicy : public JObject, public JRejectedExecutionHandler {
            public:
                JDiscardPolicy():JObject(getClazz()) { 
                }

                static JClass* getClazz();

                virtual void rejectedExecution(JRunnable* r, JThreadPoolExecutor* e) {
                }
            };

            // @Class(canonicalName="java.util.concurrent.ThreadPoolExecutor$DiscardOldestPolicy", simpleName="ThreadPoolExecutor$DiscardOldestPolicy");
            class JDiscardOldestPolicy : public JObject, public JRejectedExecutionHandler {
            public:
                JDiscardOldestPolicy() :JObject(getClazz()) { 
                }

                static JClass* getClazz();

                virtual void rejectedExecution(JRunnable* r, JThreadPoolExecutor* e) {
                    if (!e->isShutdown()) {
                        dynamic_cast<JQueue*>(e->getQueue())->poll();
                        e->execute(r);
                    }
                }
            };

            JRejectedExecutionHandler* JThreadPoolExecutor::defaultHandler =new JAbortPolicy();

            JThreadPoolExecutor::~JThreadPoolExecutor(){
            }
        }
    }
}
