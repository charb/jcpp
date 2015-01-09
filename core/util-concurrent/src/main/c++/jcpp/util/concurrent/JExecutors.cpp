#include "jcpp/util/concurrent/JExecutors.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/util/concurrent/JThreadFactory.h"
#include "jcpp/util/concurrent/JThreadPoolExecutor.h"
#include "jcpp/util/concurrent/JScheduledThreadPoolExecutor.h"
#include "jcpp/util/concurrent/JSynchronousQueue.h"
#include "jcpp/util/concurrent/atomic/JAtomicInteger.h"
#include "jcpp/lang/JRunnable.h"
#include "jcpp/lang/JNullPointerException.h"

using namespace jcpp::util::concurrent::atomic;

namespace jcpp{
    namespace util{
        namespace concurrent{

            // @Class(canonicalName="java.util.concurrent.Executors$RunnableAdapter", simpleName="Executors$RunnableAdapter");
            class JRunnableAdapter : public JObject, public JCallable {
            protected:
                JRunnable* task;
                JObject* result;

            public:
                JRunnableAdapter(JRunnable* task, JObject* result) :JObject(getClazz()){
                    this->task = task;
                    this->result = result;
                }

                static JClass* getClazz();

                virtual JObject* call() {
                    task->run();
                    return result;
                }
            };

            JCallable* JExecutors::callable(JRunnable* r,JObject* result){
                if (r == null){
                    throw new JNullPointerException();
                }
                return new JRunnableAdapter(r, result);
            }

            static jint poolNumber = 0;

            // @Class(canonicalName="java.util.concurrent.Executors$DefaultThreadFactory", simpleName="Executors$DefaultThreadFactory");
            class JDefaultThreadFactory : public JObject, public JThreadFactory {
                JString* namePrefix;
                JAtomicInteger* threadNumber;

            public:
                JDefaultThreadFactory() :JObject(getClazz()){
                    threadNumber=new JAtomicInteger();
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("pool-")->append(poolNumber++)->append("-thread-");
                    namePrefix = builder->toString();
                }

                static JClass* getClazz();

                virtual JThread* newThread(JRunnable* r) {
                    JStringBuilder* buffer=new JStringBuilder();
                    buffer->append(namePrefix)->append(threadNumber->getAndIncrement());
                    JThread* t = new JThread(r, buffer->toString());
                    if (t->getPriority() != JThread::NORM_PRIORITY){
                        t->setPriority(JThread::NORM_PRIORITY);
                    }
                    return t;
                }
            };

            JThreadFactory* JExecutors::defaultThreadFactory(){
                return new JDefaultThreadFactory();
            }

            JExecutorService* JExecutors::newCachedThreadPool(){
                return new JThreadPoolExecutor(0, JInteger::MAX_VALUE,60000,new JSynchronousQueue());
            }

            JExecutorService* JExecutors::newCachedThreadPool(JThreadFactory* threadFactory){
                return new JThreadPoolExecutor(0, JInteger::MAX_VALUE,60000,new JSynchronousQueue(),threadFactory);
            }

            JScheduledExecutorService* JExecutors::newScheduledThreadPool(jint corePoolSize){
                return new JScheduledThreadPoolExecutor(corePoolSize);
            }

            JExecutors::~JExecutors(){
            }
        }
    }
}
