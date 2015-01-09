#include "jcpp/util/concurrent/JScheduledThreadPoolExecutor.h"
#include "jcpp/util/concurrent/JExecutors.h"
#include "jcpp/util/concurrent/JRejectedExecutionException.h"
#include "jcpp/util/JQueue.h"
#include "jcpp/util/JAbstractQueue.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/util/JHashSet.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/lang/JError.h"
#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JIllegalThreadStateException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JLong.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.ScheduledThreadPoolExecutor$ScheduledFutureTask", simpleName="ScheduledThreadPoolExecutor$ScheduledFutureTask");
            class JScheduledFutureTask : public virtual JFutureTask, public virtual JRunnableScheduledFuture {
            protected:
                JScheduledThreadPoolExecutor* executor;
                jlong sequenceNumber;
                jlong time;
                jlong period;
                JRunnableScheduledFuture* outerTask;
                jint heapIndex;
                friend class JDelayedWorkQueue;
                friend class JScheduledThreadPoolExecutor;
            
            public:
                JScheduledFutureTask(JScheduledThreadPoolExecutor* executor,JRunnable* r, JObject* result, jlong ns) : JFutureTask(getClazz(),r,result) {
                    this->executor=executor;
                    this->time = ns;
                    this->period = 0;
                    this->sequenceNumber = JScheduledThreadPoolExecutor::sequencer->getAndIncrement();
                    outerTask = this;
                    heapIndex=0;
                }

                JScheduledFutureTask(JScheduledThreadPoolExecutor* executor,JRunnable* r, JObject* result, jlong ns, jlong period): JFutureTask(getClazz(), r, result){
                    this->executor=executor;
                    this->time = ns;
                    this->period = period;
                    this->sequenceNumber = JScheduledThreadPoolExecutor::sequencer->getAndIncrement();
                    outerTask = this;
                    heapIndex=0;
                }

                JScheduledFutureTask(JScheduledThreadPoolExecutor* executor,JCallable* callable, jlong ns): JFutureTask(getClazz(),callable){
                    this->executor=executor;
                    this->time = ns;
                    this->period = 0;
                    this->sequenceNumber =  JScheduledThreadPoolExecutor::sequencer->getAndIncrement();
                    outerTask = this;
                    heapIndex=0;
                }

                static JClass* getClazz();

                virtual jlong getDelay() {
                    return time - executor->now();
                }

                virtual jint compareTo(JObject* obj) {
                    if (obj == this){
                        return 0;
                    }
                    JDelayed* other=dynamic_cast<JDelayed*>(obj);
                    if (obj->isInstanceOf(JScheduledFutureTask::getClazz())) {
                        JScheduledFutureTask* x = dynamic_cast<JScheduledFutureTask*>(other);
                        jlong diff = time - x->time;
                        if (diff < 0){
                            return -1;
                        }else if (diff > 0){
                            return 1;
                        }else if (sequenceNumber < x->sequenceNumber){
                            return -1;
                        }else{
                            return 1;
                        }
                    }
                    jlong diff = getDelay() - other->getDelay();
                    return (diff < 0) ? -1 : (diff > 0) ? 1 : 0;
                }

                virtual jbool isPeriodic() {
                    return period != 0;
                }

                virtual void setNextRunTime() {
                    jlong p = period;
                    if (p > 0){
                        time += p;
                    }else{
                        time = executor->triggerTime(-p);
                    }
                }

                virtual jbool cancel() {
                    jbool cancelled = JFutureTask::cancel();
                    if (cancelled && executor->removeOnCancel && heapIndex >= 0){
                        executor->remove(dynamic_cast<JRunnable*>(this));
                    }
                    return cancelled;
                }

                virtual void run() {
                    jbool periodic = isPeriodic();
                    if (!executor->canRunInCurrentRunState(periodic)){
                        cancel();

                    }else if (!periodic){
                        JScheduledFutureTask::run();

                    }else if (JScheduledFutureTask::runAndReset()) {
                        setNextRunTime();
                        executor->reExecutePeriodic(outerTask);
                    }
                }
            };

            // @Class(canonicalName="java.util.concurrent.ScheduledThreadPoolExecutor$DelayedWorkQueue", simpleName="ScheduledThreadPoolExecutor$DelayedWorkQueue");
            class JDelayedWorkQueue : public JAbstractQueue, public JBlockingQueue {
            protected:
                static const jint INITIAL_CAPACITY = 16;
                JPrimitiveObjectArray* queue;
                JReentrantLock* lock;
                jint isize;
                JThread* leader;
                JCondition* available;

            public:
                JDelayedWorkQueue():JAbstractQueue(getClazz()){
                    queue=new JPrimitiveObjectArray(JRunnableScheduledFuture::getClazz(),INITIAL_CAPACITY);
                    lock = new JReentrantLock();
                    isize = 0;
                    leader = null;
                    available = lock->newCondition();
                }

                static JClass* getClazz();

                virtual void setIndex(JRunnableScheduledFuture* f, jint idx) {
                    if (dynamic_cast<JObject*>(f)->isInstanceOf(JScheduledFutureTask::getClazz())) {
                        (dynamic_cast<JScheduledFutureTask*>(f))->heapIndex = idx;
                    }
                }

                virtual void siftUp(jint k, JRunnableScheduledFuture* key) {
                    while (k > 0) {
                        jint parent = (k - 1) >> 1;
                        JRunnableScheduledFuture* e = dynamic_cast<JRunnableScheduledFuture*>(queue->get(parent));
                        if (key->compareTo(dynamic_cast<JObject*>(e)) >= 0){
                            break;
                        }
                        queue->set(k, dynamic_cast<JObject*>(e));
                        setIndex(e, k);
                        k = parent;
                    }
                    queue->set(k, dynamic_cast<JObject*>(key));
                    setIndex(key, k);
                }

                virtual void siftDown(jint k, JRunnableScheduledFuture* key) {
                    jint half = isize >> 1;
                    while (k < half) {
                        jint child = (k << 1) + 1;
                        JRunnableScheduledFuture* c = dynamic_cast<JRunnableScheduledFuture*>(queue->get(child));
                        jint right = child + 1;
                        if (right < isize && c->compareTo(queue->get(right)) > 0){
                            c = dynamic_cast<JRunnableScheduledFuture*>(queue->get(child = right));
                        }
                        if (key->compareTo(dynamic_cast<JObject*>(c)) <= 0){
                            break;
                        }
                        queue->set(k, dynamic_cast<JObject*>(c));
                        setIndex(c, k);
                        k = child;
                    }
                    queue->set(k, dynamic_cast<JObject*>(key));
                    setIndex(key, k);
                }

                virtual void grow() {
                    jint oldCapacity = queue->size();
                    jint newCapacity = oldCapacity + (oldCapacity >> 1);
                    if (newCapacity < 0){
                        newCapacity = JInteger::MAX_VALUE;
                    }
                    queue = JArrays::copyOf(queue, newCapacity);
                }

                virtual jint indexOf(JObject* x) {
                    if (x != null) {
                        if (x->isInstanceOf(JScheduledFutureTask::getClazz())) {
                            jint i = (dynamic_cast<JScheduledFutureTask*>(x))->heapIndex;
                            if (i >= 0 && i < isize && queue->get(i) == x){
                                return i;
                            }
                        } else {
                            for (jint i = 0; i < isize; i++){
                                if (x->equals(queue->get(i))){
                                    return i;
                                }
                            }
                        }
                    }
                    return -1;
                }

                virtual jbool contains(JObject* x) {
                    jbool res=false;
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        res=indexOf(x) != -1;
                    },{
                        lock->unlock();
                    })
                    return res;
                }

                virtual jbool remove(JObject* x) {
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    jbool res=false;
                    try_finally({
                        jint i = indexOf(x);
                        if (i >= 0){
                            setIndex(dynamic_cast<JRunnableScheduledFuture*>(queue->get(i)), -1);
                            jint s = --isize;
                            JRunnableScheduledFuture* replacement = dynamic_cast<JRunnableScheduledFuture*>(queue->get(s));
                            queue->set(s, null);
                            if (s != i) {
                                siftDown(i, replacement);
                                if (queue->get(i) == dynamic_cast<JObject*>(replacement)){
                                    siftUp(i, replacement);
                                }
                            }
                            res=true;
                        }
                    },{
                        lock->unlock();
                    })
                    return res;
                }

                virtual jint size() {
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    jint i=0;
                    try_finally({
                        i=isize;
                    },{
                        lock->unlock();
                    })
                    return i;
                }

                virtual jbool isEmpty() {
                    return size() == 0;
                }

                virtual jint remainingCapacity() {
                    return JInteger::MAX_VALUE;
                }

                virtual JObject* peek() {
                    JObject* res=null;
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        res=queue->get(0);
                    },{
                        lock->unlock();
                    })
                    return res;
                }

                virtual jbool offer(JObject* x) {
                    if (x == null){
                        throw new JNullPointerException();
                    }
                    JRunnableScheduledFuture* e = dynamic_cast<JRunnableScheduledFuture*>(x);
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        jint i = isize;
                        if (i >= queue->size()){
                            grow();
                        }
                        isize = i + 1;
                        if (i == 0) {
                            queue->set(0, dynamic_cast<JObject*>(e));
                            setIndex(e, 0);
                        } else {
                            siftUp(i, e);
                        }
                        if (queue->get(0) == dynamic_cast<JObject*>(e)) {
                            leader = null;
                            available->signal();
                        }
                    },{
                        lock->unlock();
                    })
                    return true;
                }

                virtual void put(JObject* e) {
                    offer(e);
                }

                virtual jbool add(JObject* e) {
                    return offer(e);
                }

                virtual jbool offer(JObject* e, jlong timeout) {
                    return offer(e);
                }

                virtual JRunnableScheduledFuture* finishPoll(JRunnableScheduledFuture* f) {
                    jint s = --isize;
                    JRunnableScheduledFuture* x = dynamic_cast<JRunnableScheduledFuture*>(queue->get(s));
                    queue->set(s, null);
                    if (s != 0){
                        siftDown(0, x);
                    }
                    setIndex(f, -1);
                    return f;
                }

                virtual JObject* poll() {
                    JObject* res=null;
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        JRunnableScheduledFuture* first = dynamic_cast<JRunnableScheduledFuture*>(queue->get(0));
                        if (first == null || first->getDelay() > 0){
                            res=null;
                        }else{
                            res=dynamic_cast<JObject*>(finishPoll(first));
                        }
                    }, {
                        lock->unlock();
                    })
                    return res;
                }

                virtual JObject* take(){
                    JObject* res=null;
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        for (;;) {
                            JRunnableScheduledFuture* first = dynamic_cast<JRunnableScheduledFuture*>(queue->get(0));
                            if (first == null){
                                available->await();
                            }else {
                                jlong delay = first->getDelay();
                                if (delay <= 0){
                                    res=dynamic_cast<JObject*>(finishPoll(first));
                                    break;
                                }
                                first = null;
                                if (leader != null){
                                    available->await();
                                }else {
                                    JThread* thisThread = JThread::currentThread();
                                    leader = thisThread;
                                    try_finally({
                                        available->await(delay);
                                    },{
                                        if (leader == thisThread){
                                            leader = null;
                                        }
                                    })
                                }
                            }
                        }
                    },{
                        if (leader == null && queue->get(0) != null){
                            available->signal();
                        }
                        lock->unlock();
                    })
                    return res;
                }

                virtual JObject* poll(jlong timeout){
                    JObject* res=null;
                    jlong nanos = timeout;
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        for (;;) {
                            JRunnableScheduledFuture* first = dynamic_cast<JRunnableScheduledFuture*>(queue->get(0));
                            if (first == null) {
                                if (nanos <= 0){
                                    res=null;
                                    break;
                                }else{
                                    nanos = available->await(nanos);
                                }
                            } else {
                                jlong delay = first->getDelay();
                                if (delay <= 0){
                                    res=dynamic_cast<JObject*>(finishPoll(first));
                                    break;
                                }
                                if (nanos <= 0){
                                    res=null;
                                    break;
                                }
                                first = null;
                                if (nanos < delay || leader != null){
                                    nanos = available->await(nanos);
                                }else {
                                    JThread* thisThread = JThread::currentThread();
                                    leader = thisThread;
                                    try_finally({
                                        jlong timeLeft = available->await(delay);
                                        nanos -= delay - timeLeft;
                                    }, {
                                        if (leader == thisThread){
                                            leader = null;
                                        }
                                    })
                                }
                            }
                        }
                    },{
                        if (leader == null && queue->get(0) != null){
                            available->signal();
                        }
                        lock->unlock();
                    })
                    return res;
                }

                virtual void clear() {
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        for (jint i = 0; i < isize; i++) {
                            JRunnableScheduledFuture* t = dynamic_cast<JRunnableScheduledFuture*>(queue->get(i));
                            if (t != null) {
                                queue->set(i, null);
                                setIndex(t, -1);
                            }
                        }
                        isize = 0;
                    } ,{
                        lock->unlock();
                    })
                }

                virtual JRunnableScheduledFuture* peekExpired() {
                    JRunnableScheduledFuture* first = dynamic_cast<JRunnableScheduledFuture*>(queue->get(0));
                    return (first == null || first->getDelay() > 0) ?null : first;
                }

                virtual jint drainTo(JCollection* c) {
                    if (c == null){
                        throw new JNullPointerException();
                    }
                    if (c == this){
                        throw new JIllegalArgumentException();
                    }
                    jint res=0;
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        JRunnableScheduledFuture* first=null;
                        jint n = 0;
                        while ((first = peekExpired()) != null) {
                            c->add(dynamic_cast<JObject*>(first));
                            finishPoll(first);
                            ++n;
                        }
                        res=n;
                    } ,{
                        lock->unlock();
                    })
                    return res;
                }

                virtual jint drainTo(JCollection* c, jint maxElements) {
                    if (c == null){
                        throw new JNullPointerException();
                    }
                    if (c == this){
                        throw new JIllegalArgumentException();
                    }
                    if (maxElements <= 0){
                        return 0;
                    }
                    jint res=0;
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        JRunnableScheduledFuture* first=null;
                        jint n = 0;
                        while (n < maxElements && (first = peekExpired()) != null) {
                            c->add(dynamic_cast<JObject*>(first));
                            finishPoll(first);
                            ++n;
                        }
                        res=n;
                    },{
                        lock->unlock();
                    })
                    return res;
                }

                virtual JPrimitiveObjectArray* toArray() {
                    JPrimitiveObjectArray* a=null;
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        a=JArrays::copyOf(queue, isize);
                    },{
                        lock->unlock();
                    })
                    return a;
                }

                virtual JPrimitiveObjectArray* toArray(JPrimitiveObjectArray* a) {
                    JPrimitiveObjectArray* newa=a;
                    JReentrantLock* lock = this->lock;
                    lock->lock();
                    try_finally({
                        if (a->size() < isize){
                            newa=JArrays::copyOf(queue, isize, a->getComponentType());
                        }else{
                            JSystem::arraycopy(queue, 0, a, 0, isize);
                            if (a->size() > isize){
                                a->set(isize, null);
                            }
                        }
                    },{
                        lock->unlock();
                    })
                    return newa;
                }

                virtual JIterator* iterator();

                virtual JObject* remove(){
                    return JAbstractQueue::remove();
                }

                virtual JObject* element(){
                    return JAbstractQueue::element();
                }
            };

            // @Class(canonicalName="java.util.concurrent.ScheduledThreadPoolExecutor$DelayedWorkQueue$Itr", simpleName="ScheduledThreadPoolExecutor$DelayedWorkQueue$Itr");
            class JItr : public JObject, public JIterator {
            protected:
                JDelayedWorkQueue* queue;
                JPrimitiveObjectArray* array;
                jint cursor;
                jint lastRet;

            public:
                JItr(JDelayedWorkQueue* queue,JPrimitiveObjectArray* array) :JObject(getClazz()) {
                    this->queue=queue;
                    this->array = array;
                    cursor = 0;
                    lastRet = -1;
                }

                static JClass* getClazz();

                virtual jbool hasNext() {
                    return cursor < array->size();
                }

                virtual JObject* next() {
                    if (cursor >= array->size()){
                        throw new JNoSuchElementException();
                    }
                    lastRet = cursor;
                    return array->get(cursor++);
                }

                virtual void remove() {
                    if (lastRet < 0){
                        throw new JIllegalStateException();
                    }
                    queue->remove(array->get(lastRet));
                    lastRet = -1;
                }
            };

            JIterator* JDelayedWorkQueue::iterator() {
                return new JItr(this,JArrays::copyOf(queue, isize));
            }

            JAtomicLong* JScheduledThreadPoolExecutor::sequencer = new JAtomicLong();
            
            jbool JScheduledThreadPoolExecutor::isShutdown(){
                return JThreadPoolExecutor::isShutdown();
            }

            jbool JScheduledThreadPoolExecutor::isTerminated(){
                return JThreadPoolExecutor::isTerminated();
            }

            jbool JScheduledThreadPoolExecutor::awaitTermination(jlong timeout){
                return JThreadPoolExecutor::awaitTermination(timeout);
            }

            jlong JScheduledThreadPoolExecutor::now(){
                return JSystem::currentTimeMillis();
            }

            jbool JScheduledThreadPoolExecutor::canRunInCurrentRunState(jbool periodic){
                return isRunningOrShutdown(periodic ? continueExistingPeriodicTasksAfterShutdown : executeExistingDelayedTasksAfterShutdown);
            }

            void JScheduledThreadPoolExecutor::delayedExecute(JRunnableScheduledFuture* task){
                if (JThreadPoolExecutor::isShutdown()){
                    reject(task);
                }else {
                    JThreadPoolExecutor::getQueue()->add(dynamic_cast<JObject*>(task));
                    if (JThreadPoolExecutor::isShutdown() && !canRunInCurrentRunState(task->isPeriodic()) && remove(task)){
                        dynamic_cast<JFuture*>(task)->cancel();
                    }else{
                        ensurePrestart();
                    }
                }
            }

            void JScheduledThreadPoolExecutor::reExecutePeriodic(JRunnableScheduledFuture* task){
                if (canRunInCurrentRunState(true)) {
                    JThreadPoolExecutor::getQueue()->add(dynamic_cast<JObject*>(task));
                    if (!canRunInCurrentRunState(true) && remove(task)){ 
                        dynamic_cast<JFuture*>(task)->cancel();
                    }else{
                        ensurePrestart();
                    }
                }
            }
            void JScheduledThreadPoolExecutor::onShutdown(){
                JBlockingQueue* q = JThreadPoolExecutor::getQueue();
                jbool keepDelayed =getExecuteExistingDelayedTasksAfterShutdownPolicy();
                jbool keepPeriodic =getContinueExistingPeriodicTasksAfterShutdownPolicy();

                if (!keepDelayed && !keepPeriodic) {
                    JPrimitiveObjectArray* a=q->toArray();
                    for (jint i=0;i<a->size();i++){
                        JObject* e =a->get(i);
                        if (e->isInstanceOf(JRunnableScheduledFuture::getClazz())){
                            dynamic_cast<JFuture*>(e)->cancel();
                        }
                    }
                    q->clear();
                
                }else {
                    JPrimitiveObjectArray* a=q->toArray();
                    for (jint i=0;i<a->size();i++){
                        JObject* e=a->get(i);
                        if (e->isInstanceOf(JRunnableScheduledFuture::getClazz())) {
                            JRunnableScheduledFuture* t = dynamic_cast<JRunnableScheduledFuture*>(e);
                            if ((t->isPeriodic() ? !keepPeriodic : !keepDelayed) || dynamic_cast<JFuture*>(t)->isCancelled()) {
                                if (q->remove(dynamic_cast<JObject*>(t))){
                                    dynamic_cast<JFuture*>(t)->cancel();
                                }
                            }
                        }
                    }
                }
                tryTerminate();
            }

            JRunnableScheduledFuture* JScheduledThreadPoolExecutor::decorateTask(JRunnable* runnable, JRunnableScheduledFuture* task){
                return task;
            }

            JRunnableScheduledFuture* JScheduledThreadPoolExecutor::decorateTask(JCallable* callable, JRunnableScheduledFuture* task){
                return task;
            }

            JScheduledThreadPoolExecutor::JScheduledThreadPoolExecutor(jint corePoolSize):JThreadPoolExecutor(getClazz(),corePoolSize, JInteger::MAX_VALUE, 0, new JDelayedWorkQueue()){
                continueExistingPeriodicTasksAfterShutdown=false;
                executeExistingDelayedTasksAfterShutdown=true;
                removeOnCancel=false;
            }

            JScheduledThreadPoolExecutor::JScheduledThreadPoolExecutor(jint corePoolSize,JThreadFactory* threadFactory):JThreadPoolExecutor(getClazz(),corePoolSize, JInteger::MAX_VALUE, 0,new JDelayedWorkQueue(), threadFactory){
                continueExistingPeriodicTasksAfterShutdown=false;
                executeExistingDelayedTasksAfterShutdown=true;
                removeOnCancel=false;   
            }

            JScheduledThreadPoolExecutor::JScheduledThreadPoolExecutor(jint corePoolSize,JRejectedExecutionHandler* handler):JThreadPoolExecutor(getClazz(),corePoolSize, JInteger::MAX_VALUE, 0, new JDelayedWorkQueue(), handler){
                continueExistingPeriodicTasksAfterShutdown=false;
                executeExistingDelayedTasksAfterShutdown=true;
                removeOnCancel=false;
            }

            JScheduledThreadPoolExecutor::JScheduledThreadPoolExecutor(jint corePoolSize,JThreadFactory* threadFactory,JRejectedExecutionHandler* handler):JThreadPoolExecutor(getClazz(),corePoolSize, JInteger::MAX_VALUE, 0,new JDelayedWorkQueue(), threadFactory, handler){
                continueExistingPeriodicTasksAfterShutdown=false;
                executeExistingDelayedTasksAfterShutdown=true;
                removeOnCancel=false;
            }
            

            jlong JScheduledThreadPoolExecutor::triggerTime(jlong delay){
                 return now() + ((delay < (JLong::MAX_VALUE >> 1)) ? delay : overflowFree(delay));
            }

            jlong JScheduledThreadPoolExecutor::overflowFree(jlong delay){
                JDelayed* head = dynamic_cast<JDelayed*>(JThreadPoolExecutor::getQueue()->peek());
                if (head != null) {
                    jlong headDelay = head->getDelay();
                    if (headDelay < 0 && (delay - headDelay < 0)){
                        delay = JLong::MAX_VALUE + headDelay;
                    }
                }
                return delay;
            }
                
            JScheduledFuture* JScheduledThreadPoolExecutor::schedule(JRunnable* command,jlong delay){
                if (command == null){
                    throw new JNullPointerException();
                }
                JRunnableScheduledFuture* t = decorateTask(command, new JScheduledFutureTask(this,command, null,triggerTime(delay)));
                delayedExecute(t);
                return t;
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::schedule(JCallable* callable,jlong delay){
                if (callable == null){
                    throw new JNullPointerException();
                }
                JRunnableScheduledFuture* t = decorateTask(callable,new JScheduledFutureTask(this,callable, triggerTime(delay)));
                delayedExecute(t);
                return t;
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::scheduleAtFixedRate(JRunnable* command,jlong initialDelay,jlong period){
                if (command == null){
                    throw new JNullPointerException();
                }
                if (period <= 0){
                    throw new JIllegalArgumentException();
                }
                JScheduledFutureTask* sft =new JScheduledFutureTask(this,command,null,triggerTime(initialDelay),period);
                JRunnableScheduledFuture* t = decorateTask(command, sft);
                sft->outerTask = t;
                delayedExecute(t);
                return t;
            }

            JScheduledFuture* JScheduledThreadPoolExecutor::scheduleWithFixedDelay(JRunnable* command,jlong initialDelay,jlong delay){
                if (command == null){
                    throw new JNullPointerException();
                }
                if (delay <= 0){
                    throw new JIllegalArgumentException();
                }
                JScheduledFutureTask* sft =new JScheduledFutureTask(this,command,null,triggerTime(initialDelay),-delay);
                JRunnableScheduledFuture* t = decorateTask(command, sft);
                sft->outerTask = t;
                delayedExecute(t);
                return t;
            }

            void JScheduledThreadPoolExecutor::execute(JRunnable* command){
                schedule(command, 0);
            }

            JFuture* JScheduledThreadPoolExecutor::submit(JRunnable* task){
                return schedule(task, 0);
            }

            JFuture* JScheduledThreadPoolExecutor::submit(JRunnable* task, JObject* result){
                return schedule(JExecutors::callable(task, result), 0);
            }

            JFuture* JScheduledThreadPoolExecutor::submit(JCallable* task){
                return schedule(task, 0);
            }

            void JScheduledThreadPoolExecutor::setContinueExistingPeriodicTasksAfterShutdownPolicy(jbool value){
                continueExistingPeriodicTasksAfterShutdown = value;
                if (!value && JThreadPoolExecutor::isShutdown()){
                    onShutdown();
                }
            }

            jbool JScheduledThreadPoolExecutor::getContinueExistingPeriodicTasksAfterShutdownPolicy(){
                return continueExistingPeriodicTasksAfterShutdown;
            }

            void JScheduledThreadPoolExecutor::setExecuteExistingDelayedTasksAfterShutdownPolicy(jbool value){
                executeExistingDelayedTasksAfterShutdown = value;
                if (!value && JThreadPoolExecutor::isShutdown()){
                    onShutdown();
                }
            }

            jbool JScheduledThreadPoolExecutor::getExecuteExistingDelayedTasksAfterShutdownPolicy(){
                return executeExistingDelayedTasksAfterShutdown;
            }

            void JScheduledThreadPoolExecutor::setRemoveOnCancelPolicy(jbool value){
                removeOnCancel = value;
            }

            jbool JScheduledThreadPoolExecutor::getRemoveOnCancelPolicy(){
                return removeOnCancel;
            }

            void JScheduledThreadPoolExecutor::shutdown(){
                JThreadPoolExecutor::shutdown();
            }

            JList* JScheduledThreadPoolExecutor::shutdownNow(){
                return JThreadPoolExecutor::shutdownNow();
            }

            JBlockingQueue* JScheduledThreadPoolExecutor::getQueue(){
                return JThreadPoolExecutor::getQueue();
            }

            JScheduledThreadPoolExecutor::~JScheduledThreadPoolExecutor(){
            }
        }
    }
}
