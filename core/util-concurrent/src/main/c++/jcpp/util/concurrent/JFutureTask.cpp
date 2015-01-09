#include "jcpp/util/concurrent/JFutureTask.h"
#include "jcpp/util/concurrent/JCancellationException.h"
#include "jcpp/util/concurrent/JExecutionException.h"
#include "jcpp/util/concurrent/JTimeoutException.h"
#include "jcpp/util/concurrent/JExecutors.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/JNullPointerException.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

            jint JFutureTask::NEW = 0 ;
            jint JFutureTask::COMPLETING=1;
            jint JFutureTask::NORMAL=2;
            jint JFutureTask::EXCEPTIONAL=3;
            jint JFutureTask::CANCELLED=4;
            jint JFutureTask::INTERRUPTING=5;
            jint JFutureTask::INTERRUPTED=6;

            JFutureTask::JFutureTask(JClass* _class,JCallable* c):JObject(_class){
                if (callable == null){
                    throw new JNullPointerException();
                }
                this->callable = c;
                this->state = new JAtomicInteger(NEW);
                outcome=null;
            }

            JFutureTask::JFutureTask(JClass* _class,JRunnable* r,JObject* result):JObject(_class){
                this->callable = JExecutors::callable(r, result);
                this->state = new JAtomicInteger(NEW); 
                outcome=null;
            }

            JFutureTask::JFutureTask(JCallable* c):JObject(getClazz()){
                if (callable == null){
                    throw new JNullPointerException();
                }
                this->callable = c;
                this->state = new JAtomicInteger(NEW);
                outcome=null;
            }

            JFutureTask::JFutureTask(JRunnable* r,JObject* result):JObject(getClazz()){
                this->callable = JExecutors::callable(r, result);
                this->state = new JAtomicInteger(NEW); 
                outcome=null;
            }

            JObject* JFutureTask::report(jint s){
                JObject* x = null;
                synchronized(this,{
                    x=outcome;
                })
                if (s == NORMAL){
                    return x;
                }
                if (s >= CANCELLED){
                    throw new JCancellationException();
                }
                throw new JExecutionException(null,dynamic_cast<JThrowable*>(x));
            }

            jbool JFutureTask::isCancelled(){
                return state->get()>=CANCELLED;
            }

            jbool JFutureTask::isDone(){
                return state->get()!=NEW;
            }

            jbool JFutureTask::cancel(){
                if (!(state->get() == NEW && state->compareAndSet( NEW, CANCELLED))){
                    return false;
                }
                //TODO should implement sthg to interrupt the thread!
                finishCompletion();
                return true;
            }

            JObject* JFutureTask::get(){
                jint s = state->get();
                if (s <= COMPLETING){
                    s = awaitDone(false, 0);
                }
                return report(s);
            }

            JObject* JFutureTask::get(jlong timeout){
                jint s = state->get();
                if (s <= COMPLETING && (s = awaitDone(true, timeout)) <= COMPLETING){
                    throw new JTimeoutException();
                }
                return report(s);
            }

            void JFutureTask::done(){
            }

            void JFutureTask::set(JObject* v) {
                if (state->compareAndSet(NEW, COMPLETING)) {
                    synchronized(this,{
                        outcome = v;
                        state->set(NORMAL);
                        notifyAll();
                    })
                    finishCompletion();
                }
            }

            void JFutureTask::setException(JThrowable* t) {
                if (state->compareAndSet(NEW, COMPLETING)) {
                    synchronized(this,{
                        outcome = t;
                        state->set(EXCEPTIONAL);
                        notifyAll();
                    })
                    finishCompletion();
                }
            }

            void JFutureTask::run() {
                if (state->get() != NEW){
                    return;
                }
                JCallable* c = callable;
                if (c != null && state->get() == NEW) {
                    try {
                        JObject* result = c->call();
                        set(result);
                    } catch (JThrowable* ex) {
                        setException(ex);
                    }
                }
            }

            jbool JFutureTask::runAndReset() {
                if (state->get() != NEW){
                    return false;
                }
                jbool ran = false;
                jint s = state->get();
                JCallable* c = callable;
                if (c != null && s == NEW) {
                    try {
                        c->call();
                        ran = true;
                    } catch (JThrowable* ex) {
                        setException(ex);
                    }
                }
                s = state->get();
                return ran && s == NEW;
            }

            void JFutureTask::finishCompletion() {
                done();
                callable = null;
            }

            jint JFutureTask::awaitDone(jbool timed, jlong l){
                jlong deadline = timed ? JSystem::currentTimeMillis() + l : 0L;
                while (!(state->get()>COMPLETING)){
                    if (timed){
                        synchronized(this,{
                            jlong t=deadline-JSystem::currentTimeMillis();
                            if (t>0){
                                wait(t);
                            }else{
                                break;
                            }
                        })
                    }else{
                        synchronized(this,{
                            wait();
                        })
                    }
                }
                return state->get();
            }

            JFutureTask::~JFutureTask(){
            }
        }
    }
}
