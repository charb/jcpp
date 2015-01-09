#include "jcpp/util/JTimer.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JSystem.h"

namespace jcpp{
    namespace util{
        class JTimerClass : public JClass{
        public:
            JTimerClass():JClass(){
                this->canonicalName=new JString("java.util.Timer");
                this->name=new JString("java.util.Timer");
                this->simpleName=new JString("Timer");
            }

            virtual JClass* getSuperclass(){
                return JObject::getClazz();
            }

            virtual void fillDeclaredClasses();
        };

        static JClass* clazz;

        JClass* JTimer::getClazz(){
            if (clazz==null){
                clazz=new JTimerClass();
            }
            return clazz;
        }

        class JTaskQueueClass : public JClass{
        public:
            JTaskQueueClass():JClass(){
                this->canonicalName=new JString("java.util.TaskQueue");
                this->name=new JString("java.util.TaskQueue");
                this->simpleName=new JString("TaskQueue");
            }

            virtual JClass* getSuperclass(){
                return JObject::getClazz();
            }

            virtual jcpp::lang::JClass* getDeclaringClass(){
                return JTimer::getClazz();
            }
        };

        static JClass* taskQueueClazz=null;

        JClass* JTimer::JTaskQueue::getClazz(){
            if (taskQueueClazz==null){
                taskQueueClazz=new JTaskQueueClass();
            }
            return taskQueueClazz;
        }

        JTimer::JTaskQueue::JTaskQueue():JObject(JTimer::JTaskQueue::getClazz()){
            queue=new JPrimitiveObjectArray(JTimerTask::getClazz(),128);
            isize=0;
        }
                
        jint JTimer::JTaskQueue::size(){
            return isize;
        }
                
        void JTimer::JTaskQueue::add(JTimerTask* task){
            if (isize + 1 == queue->size()){
                queue = JArrays::copyOf(queue, 2*queue->size());
            }
            queue->set(++isize, task);
            fixUp(isize);
        }
        
        JTimerTask* JTimer::JTaskQueue::getMin(){
            return dynamic_cast<JTimerTask*>(queue->get(1));
        }
                
        JTimerTask* JTimer::JTaskQueue::get(jint i){
            return dynamic_cast<JTimerTask*>(queue->get(i));
        }
                
        void JTimer::JTaskQueue::removeMin(){
            queue->set(1, queue->get(isize));
            queue->set(isize--, null);
            fixDown(1);
        }
        
        void JTimer::JTaskQueue::quickRemove(jint i){
            queue->set(i, queue->get(isize));
            queue->set(isize--, null);
        }
                
        void JTimer::JTaskQueue::rescheduleMin(jlong newTime){
            dynamic_cast<JTimerTask*>(queue->get(1))->nextExecutionTime = newTime;
            fixDown(1);
        }
        
        jbool JTimer::JTaskQueue::isEmpty(){
            return isize==0;
        }
        
        void JTimer::JTaskQueue::clear(){
            for (jint i=1; i<=isize; i++){
                queue->set(i, null);
            }
            isize = 0;
        }
        
        void JTimer::JTaskQueue::fixUp(jint k){
            while (k > 1) {
                jint j = k >> 1;
                if (dynamic_cast<JTimerTask*>(queue->get(j))->nextExecutionTime <= dynamic_cast<JTimerTask*>(queue->get(k))->nextExecutionTime){
                    break;
                }
                JTimerTask* tmp = dynamic_cast<JTimerTask*>(queue->get(j));
                queue->set(j, queue->get(k));
                queue->set(k, tmp);
                k = j;
            }
        }
        
        void JTimer::JTaskQueue::fixDown(jint k){
            jint j=0;
            while ((j = k << 1) <= isize && j > 0) {
                if (j < isize && dynamic_cast<JTimerTask*>(queue->get(j))->nextExecutionTime > dynamic_cast<JTimerTask*>(queue->get(j+1))->nextExecutionTime){
                    j++;
                }
                if (dynamic_cast<JTimerTask*>(queue->get(k))->nextExecutionTime <= dynamic_cast<JTimerTask*>(queue->get(j))->nextExecutionTime){
                    break;
                }
                JTimerTask* tmp = dynamic_cast<JTimerTask*>(queue->get(j));
                queue->set(j, queue->get(k));
                queue->set(k, tmp);
                k = j;
            }
        }
        
        void JTimer::JTaskQueue::heapify(){
            for (jint i = isize/2; i >= 1; i--){
                fixDown(i);
            }
        }

        JTimer::JTaskQueue::~JTaskQueue(){
        }

        class JTimerThreadClass : public JClass{
        public:
            JTimerThreadClass():JClass(){
                this->canonicalName=new JString("java.util.TimerThread");
                this->name=new JString("java.util.TimerThread");
                this->simpleName=new JString("TimerThread");
            }

            virtual JClass* getSuperclass(){
                return JThread::getClazz();
            }

            virtual jcpp::lang::JClass* getDeclaringClass(){
                return JTimer::getClazz();
            }
        };

        static JClass* timerThreadClazz=null;

        JClass* JTimer::JTimerThread::getClazz(){
            if (timerThreadClazz==null){
                timerThreadClazz=new JTimerThreadClass();
            }
            return timerThreadClazz;
        }

        JTimer::JTimerThread::JTimerThread(JTaskQueue* queue):JThread(JTimer::JTimerThread::getClazz()){
            newTasksMayBeScheduled=true;
            this->queue=queue;
        }

        void JTimer::JTimerThread::run() {
            try {
                mainLoop();
            } catch(...) {
                synchronized(queue,{
                    newTasksMayBeScheduled = false;
                    queue->clear();
                })
            }
        }

        void JTimer::JTimerThread::mainLoop() {
            while (true) {
                JTimerTask* task=null;
                jbool taskFired;
                synchronized(queue,{
                    while (queue->isEmpty() && newTasksMayBeScheduled){
                        queue->wait();
                    }
                    if (queue->isEmpty()){
                        break;
                    }

                    jlong currentTime=0;
                    jlong executionTime=0;
                    task = queue->getMin();
                    synchronized(task->lockObject,{
                        if (task->state == JTimerTask::CANCELLED) {
                            queue->removeMin();
                            continue;
                        }
                        currentTime = JSystem::currentTimeMillis();
                        executionTime = task->nextExecutionTime;
                        if (taskFired = (executionTime<=currentTime)) {
                            if (task->period == 0) {
                                queue->removeMin();
                                task->state = JTimerTask::EXECUTED;
                            } else {
                                queue->rescheduleMin(task->period<0 ? currentTime   - task->period : executionTime + task->period);
                            }
                        }
                    })
                    if (!taskFired){
                        queue->wait(executionTime - currentTime);
                    }
                })
                if (taskFired){
                    task->run();
                }
            }
        }

        JTimer::JTimerThread::~JTimerThread(){
        }

        jint JTimer::nextSerialNumber = 0;
        
        jint JTimer::serialNumer(){
            synchronized(getClazz(),{
                return nextSerialNumber++;
            })
        }

        JTimer::JTimer():JObject(getClazz()){
            queue=new JTaskQueue();
            thread=new JTimerThread(queue);
            thread->setName(new JString("Timer-"+serialNumer()));
            thread->start();
        }

        JTimer::JTimer(JClass* _class):JObject(_class){
            queue=new JTaskQueue();
            thread=new JTimerThread(queue);
            thread->setName(new JString("Timer-"+serialNumer()));
            thread->start();
        }

        JTimer::JTimer(jbool isDaemon):JObject(getClazz()){
            queue=new JTaskQueue();
            thread=new JTimerThread(queue);
            thread->setName(new JString("Timer-"+serialNumer()));
            thread->setDaemon(isDaemon);
            thread->start();
        }

        JTimer::JTimer(JString* name):JObject(getClazz()){
            queue=new JTaskQueue();
            thread=new JTimerThread(queue);
            thread->setName(name);
            thread->start();
        }

        JTimer::JTimer(JString* name,jbool isDaemon):JObject(getClazz()){
            queue=new JTaskQueue();
            thread=new JTimerThread(queue);
            thread->setName(name);
            thread->setDaemon(isDaemon);
            thread->start();
        }

        void JTimer::schedule(JTimerTask* task, jlong delay) {
            if (delay < 0){
                throw new JIllegalArgumentException(new JString("Negative delay."));
            }
            sched(task, JSystem::currentTimeMillis()+delay, 0);
        }

        void JTimer::schedule(JTimerTask* task, jlong delay, jlong period) {
            if (delay < 0){
                throw new JIllegalArgumentException(new JString("Negative delay."));
            }
            if (period <= 0){
                throw new JIllegalArgumentException(new JString("Non-positive period."));
            }
            sched(task, JSystem::currentTimeMillis()+delay, -period);
        }

        void JTimer::scheduleAtFixedRate(JTimerTask* task, jlong delay, jlong period) {
            if (delay < 0){
                throw new JIllegalArgumentException(new JString("Negative delay."));
            }
            if (period <= 0){
                throw new JIllegalArgumentException(new JString("Non-positive period."));
            }
            sched(task, JSystem::currentTimeMillis()+delay, period);
        }

        void JTimer::sched(JTimerTask* task, jlong time, jlong period) {
            if (time < 0){
                throw new JIllegalArgumentException(new JString("Illegal execution time."));
            }

            if ((period>0 ? period : -period) > (JLong::MAX_VALUE >> 1)){
                period >>= 1;
            }

            synchronized(queue, {
                if (!thread->newTasksMayBeScheduled){
                    throw new JIllegalStateException(new JString("Timer already cancelled."));
                }

                synchronized(task->lockObject, {
                    if (task->state != JTimerTask::VIRGIN){
                        throw new JIllegalStateException(new JString("Task already scheduled or cancelled"));
                    }
                    task->nextExecutionTime = time;
                    task->period = period;
                    task->state = JTimerTask::SCHEDULED;
                })

                queue->add(task);
                if (queue->getMin() == task){
                    queue->notify();
                }
            })
        }

        void JTimer::cancel() {
            synchronized(queue, {
                thread->newTasksMayBeScheduled = false;
                queue->clear();
                queue->notify();
            })
        }

        jint JTimer::purge() {
            jint result = 0;

            synchronized(queue, {
                for (jint i = queue->size(); i > 0; i--) {
                    if (dynamic_cast<JTimerTask*>(queue->get(i))->state == JTimerTask::CANCELLED) {
                        queue->quickRemove(i);
                        result++;
                    }
                }

                if (result != 0){
                    queue->heapify();
                }
            })

            return result;
        }

        void JTimerClass::fillDeclaredClasses(){
            addDeclaredClass(JTimer::JTaskQueue::getClazz());
            addDeclaredClass(JTimer::JTimerThread::getClazz());
        }

        JTimer::~JTimer(){
        }
    }
}
