#include "jcpp/util/concurrent/locks/JLocksTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicInteger.h"
#include "jcpp/util/concurrent/locks/JLock.h"
#include "jcpp/util/concurrent/locks/JCondition.h"
#include "jcpp/util/concurrent/locks/JReadWriteLock.h"
#include "jcpp/util/concurrent/locks/JReentrantLock.h"
#include "jcpp/util/concurrent/locks/JReentrantReadWriteLock.h"
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
            namespace locks{


                JLocksTest::JLocksTest():JAbstractTest(getClazz(),new JString("test")){
                }


            	// @Class(canonicalName="jcpp.util.concurrent.locks.LocksTest$ThreadWriterLocks", simpleName="LocksTest$ThreadWriterLocks");
                class JThreadWriterLocks : public JThread{
                protected:
                    JLock* l;
                    JCondition* cond;
                    JAtomicInteger* ai;
                    JReentrantReadWriteLock* wrLock;
                    JAtomicInteger* nbReadLock;
                    JAtomicInteger* nbWriteLock;

                public:
                    JThreadWriterLocks(JLock* l,JCondition* cond,JAtomicInteger* ai,JReentrantReadWriteLock* wrLock,JAtomicInteger* nbReadLock,JAtomicInteger* nbWriteLock):JThread(getClazz()){
                        this->l=l;
                        this->cond=cond;
                        this->ai=ai;
                        this->wrLock=wrLock;
                        this->nbReadLock=nbReadLock;
                        this->nbWriteLock=nbWriteLock;
                    }

                    static JClass* getClazz();

                    virtual void run(){
                        try{
                            JStringBuilder* builder=new JStringBuilder();
                            builder->append(JThread::currentThread())
                                   ->append(": before RDV");
                            JSystem::out->println(builder->toString());

                            l->lock();
                            ai->incrementAndGet();
                            cond->await();
                            ai->decrementAndGet();
                            l->unlock();

                            builder=new JStringBuilder();
                            builder->append(JThread::currentThread())
                                   ->append(": after RDV");
                            JSystem::out->println(builder->toString());

                            for (jint i=0;i<30;i++){
                                builder=new JStringBuilder();
                                builder->append(JThread::currentThread())
                                       ->append(": read locking");
                                JSystem::out->println(builder->toString());
                                wrLock->readLock()->lock();
                                nbReadLock->incrementAndGet();
                                JLocksTest::assertEquals(nbWriteLock->get(),0);
                                nbReadLock->decrementAndGet();
                                wrLock->readLock()->unlock();


                                builder=new JStringBuilder();
                                builder->append(JThread::currentThread())
                                       ->append(": before write locking");
                                JSystem::out->println(builder->toString());
                                wrLock->writeLock()->lock();
                                nbWriteLock->incrementAndGet();
                                builder=new JStringBuilder();
                                builder->append(JThread::currentThread())
                                       ->append(": write locked");
                                JSystem::out->println(builder->toString());
                                JLocksTest::assertEquals(nbReadLock->get(),0);
                                JLocksTest::assertEquals(nbWriteLock->get(),1);
                                nbWriteLock->decrementAndGet();
                                wrLock->writeLock()->unlock();
                                builder=new JStringBuilder();
                                builder->append(JThread::currentThread())
                                       ->append(": write unlocked!");
                                JSystem::out->println(builder->toString());
                            }
                        }catch(JThrowable* th){
                            JStringBuilder* builder=new JStringBuilder();
                            builder->append(JThread::currentThread())
                                   ->append(": error happened!");
                            JSystem::out->println(builder->toString());
                            th->printStackTrace();
                        }
                    }
                };

                void JLocksTest::test(){
                    JAtomicInteger* ai=new JAtomicInteger(0);
                    JAtomicInteger* nbReadLock=new JAtomicInteger(0);
                    JAtomicInteger* nbWriteLock=new JAtomicInteger(0);

                    JReentrantLock* l=new JReentrantLock();
                    JCondition* rdv=l->newCondition();
                    JReentrantReadWriteLock* wrLock=new JReentrantReadWriteLock();

                    JPrimitiveObjectArray* array=new JPrimitiveObjectArray(JThreadWriterLocks::getClazz(),5);
                    for (jint i=0;i<array->size();i++){
                        JThreadWriterLocks* tw=new JThreadWriterLocks(l,rdv,ai,wrLock,nbReadLock,nbWriteLock);
                        tw->start();
                        array->set(i,tw);
                    }

                    l->lock();
                    while (ai->get()!=5){
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append(JThread::currentThread())
                               ->append(": main thread waiting RDV");
                        JSystem::out->println(builder->toString());
                        rdv->await(1000);
                    }
                    rdv->signalAll();
                    l->unlock();

                    JStringBuilder* builder=new JStringBuilder();
                    builder->append(JThread::currentThread())
                           ->append(": main thread RDV succeeded!");
                    JSystem::out->println(builder->toString());

                    for (jint i=0;i<array->size();i++){
                        JThreadWriterLocks* tw=dynamic_cast<JThreadWriterLocks*>(array->get(i));
                        builder=new JStringBuilder();
                        builder->append(tw)
                               ->append(": waiting EOL");
                        JSystem::out->println(builder->toString());
                        while (tw->isAlive()){
                            JThread::sleep(1000);
                        }
                    }
                }

                JLocksTest::~JLocksTest(){
                }
            }
        }
    }
}
