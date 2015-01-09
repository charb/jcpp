#include "jcpp/util/concurrent/JExecutorServiceTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicInteger.h"
#include "jcpp/util/concurrent/JExecutorService.h"
#include "jcpp/util/concurrent/JExecutor.h"
#include "jcpp/util/concurrent/JExecutors.h"
#include "jcpp/util/concurrent/JFuture.h"
#include "jcpp/util/concurrent/JCallable.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;
using namespace jcpp::util::concurrent::atomic;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JExecutorServiceTest::JExecutorServiceTest():JAbstractTest(getClazz(),new JString("test")){
            }

        	// @Class(canonicalName="jcpp.util.concurrent.locks.ExecutorServiceTest$CallableExecutorService", simpleName="ExecutorServiceTest$CallableExecutorService");
            class JCallableExecutorService : public JObject, public JCallable{
            public:
                JCallableExecutorService():JObject(getClazz()){
                }

                static JClass* getClazz();

                virtual JObject* call(){
                    JInteger* in=new JInteger(1);
                    JThread::sleep(2000);
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append(JThread::currentThread())
                           ->append(" : calling callable.");
                    JSystem::out->println(builder->toString());
                    return in;
                }
            };



        	// @Class(canonicalName="jcpp.util.concurrent.locks.ExecutorServiceTest$RunnableExecutorService", simpleName="ExecutorServiceTest$RunnableExecutorService");
            class JRunnableExecutorService : public JObject, public JRunnable{
            protected:
                JAtomicInteger* ai;

            public:
                JRunnableExecutorService(JAtomicInteger* ai):JObject(getClazz()){
                    this->ai=ai;
                }

                static JClass* getClazz();

                virtual void run(){
                    ai->incrementAndGet();
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append(JThread::currentThread())
                           ->append(" : calling runnable.");
                    JSystem::out->println(builder->toString());
                }
            };



            void JExecutorServiceTest::test(){
                try{
                    JExecutorService* executor=JExecutors::newCachedThreadPool();

                    JPrimitiveObjectArray* futures=new JPrimitiveObjectArray(JFuture::getClazz(),5);
                    for (jint i=0;i<futures->size();i++){
                        JFuture* future=executor->submit(new JCallableExecutorService());
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append("Testing thread pool : future created == ")
                               ->append(dynamic_cast<JObject*>(future));
                        JSystem::out->println(builder->toString());
                        futures->set(i,dynamic_cast<JObject*>(future));
                    }
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("Testing thread pool : submit finished.");
                    JSystem::out->println(builder->toString());

                    jint total=0;
                    for (jint i=0;i<futures->size();i++){
                        JFuture* future=dynamic_cast<JFuture*>(futures->get(i));
                        builder=new JStringBuilder();
                        builder->append("Testing thread pool : waiting for future ")
                               ->append(dynamic_cast<JObject*>(future));
                        JSystem::out->println(builder->toString());
                        JInteger* in=dynamic_cast<JInteger*>(future->get());
                        total+=in->intValue();
                    }
                    assertEquals(total,5);
                    builder=new JStringBuilder();
                    builder->append("Testing thread pool : test finished!");
                    JSystem::out->println(builder->toString());

                    executor->shutdown();

                    //scheduled test
                    JScheduledExecutorService* sexecutor=JExecutors::newScheduledThreadPool(1);
                    JAtomicInteger* ai=new JAtomicInteger(0);
                    JPrimitiveObjectArray* sfutures=new JPrimitiveObjectArray(JScheduledFuture::getClazz(),5);
                    for (jint i=0;i<sfutures->size();i++){
                        JScheduledFuture* sfuture=sexecutor->scheduleAtFixedRate(new JRunnableExecutorService(ai),2000,2000);
                        sfutures->set(i,dynamic_cast<JObject*>(sfuture));
                    }
                    builder=new JStringBuilder();
                    builder->append("Testing scheduled thread pool : submit finished.");
                    JSystem::out->println(builder->toString());
                    JThread::sleep(10000);

                    for (jint i=0;i<sfutures->size();i++){
                        JScheduledFuture* sfuture=dynamic_cast<JScheduledFuture*>(sfutures->get(i));
                        sfuture->cancel();
                    }
                    assertTrue(new JString("Number of runnable called"),ai->get()>15);
                    sexecutor->shutdown();


                }catch(JThrowable* th){
                    th->printStackTrace();
                    throw th;
                }
            }

            JExecutorServiceTest::~JExecutorServiceTest(){
            }
        }
    }
}
