#include "jcpp/util/concurrent/locks/JReentrantReadWriteLock.h"
#include "jcpp/util/concurrent/locks/JCondition.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInstantiationException.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace locks{

                JReentrantReadWriteLock::JReentrantReadWriteLock(){
                    nbRead=0;
                    isThereWrite=false;
                    theLock=new JObject();
                }

                void JReentrantReadWriteLock::incrementRead(){
                    nbRead++;
                }

                void JReentrantReadWriteLock::decrementRead(){
                    nbRead--;
                }

                void JReentrantReadWriteLock::writeAdded(){
                    isThereWrite=true;
                }

                void JReentrantReadWriteLock::writeRemoved(){
                    isThereWrite=false;
                }

                // @Class(canonicalName="java.util.concurrent.ReentrantReadWriteLock$ConditionObject", simpleName="ReentrantReadWriteLock$ConditionObject");
                class JReadWriteLockConditionObject : public JCondition, public JObject{
                    JReentrantReadWriteLock* reentrantReadWriteLock;
                    jbool signaled;

                public:
                    JReadWriteLockConditionObject(JReentrantReadWriteLock* reentrantReadWriteLock){
                        this->reentrantReadWriteLock=reentrantReadWriteLock;
                        this->signaled=false;
                    }

                    static JClass* getClazz();

                    virtual void await(){
                        synchronized(reentrantReadWriteLock->theLock,{
                            signaled=false;
                            while (!signaled){
                                reentrantReadWriteLock->theLock->wait();
                            }
                        })
                    }

                    virtual jlong await(jlong l){
                        synchronized(reentrantReadWriteLock->theLock,{
                            signaled=false;
                            while (!signaled && l>0){
                                jlong l1=JSystem::currentTimeMillis();
                                reentrantReadWriteLock->theLock->wait(l);
                                l1=JSystem::currentTimeMillis()-l1;
                                l-=l1;
                            }
                            return (l<0 ? 0 : l);
                        })
                    }

                    virtual void signal(){
                        synchronized(reentrantReadWriteLock->theLock,{
                            signaled=true;
                            reentrantReadWriteLock->theLock->notify();
                        })
                    }

                    virtual void signalAll(){
                        synchronized(reentrantReadWriteLock->theLock,{
                            signaled=true;
                            reentrantReadWriteLock->theLock->notifyAll();
                        })
                    }

                    virtual ~JReadWriteLockConditionObject(){
                    }
                };

                // @Class(canonicalName="java.util.concurrent.ReentrantReadWriteLock$ReadLock", simpleName="ReentrantReadWriteLock$ReadLock");
                class JReadLock : public JLock , public JObject{
                protected:
                    JReentrantReadWriteLock* reentrantReadWriteLock;

                public:
                    JReadLock(JReentrantReadWriteLock* l){
                        reentrantReadWriteLock=l;
                    }

                    static JClass* getClazz();

                    virtual void lock(){
                        synchronized(reentrantReadWriteLock->theLock,{
                            while (reentrantReadWriteLock->isThereWrite){
                                reentrantReadWriteLock->theLock->wait();
                            }
                            reentrantReadWriteLock->incrementRead();
                        })
                    }

                    virtual jbool tryLock(){
                        synchronized(reentrantReadWriteLock->theLock,{
                            if (!reentrantReadWriteLock->isThereWrite){
                                reentrantReadWriteLock->incrementRead();
                                return true;
                            }
                            return false;
                        })
                    }

                    virtual jbool tryLock(jlong l){
                        synchronized(reentrantReadWriteLock->theLock,{
                            while (reentrantReadWriteLock->isThereWrite && l>0){
                                jlong l1=JSystem::currentTimeMillis();
                                reentrantReadWriteLock->theLock->wait(l);
                                l1=JSystem::currentTimeMillis()-l1;
                                l-=l1;
                            }
                            if (!reentrantReadWriteLock->isThereWrite){
                                reentrantReadWriteLock->incrementRead();
                                return true;
                            }
                            return false;
                        })
                    }

                    virtual void unlock(){
                        synchronized(reentrantReadWriteLock->theLock,{
                            reentrantReadWriteLock->decrementRead();
                            reentrantReadWriteLock->theLock->notifyAll();
                        })
                    }

                    virtual JCondition* newCondition(){
                        return new JReadWriteLockConditionObject(reentrantReadWriteLock);
                    }

                    virtual ~JReadLock(){
                    }
                };
                    
                JLock* JReentrantReadWriteLock::readLock(){
                    return new JReadLock(this);
                }

                // @Class(canonicalName="java.util.concurrent.ReentrantReadWriteLock$WriteLock", simpleName="ReentrantReadWriteLock$WriteLock");
                class JWriteLock : public JLock , public JObject{
                protected:
                    JReentrantReadWriteLock* reentrantReadWriteLock;
                    
                public:
                    JWriteLock(JReentrantReadWriteLock* l){
                        reentrantReadWriteLock=l;
                    }

                    static JClass* getClazz();

                    virtual void lock(){
                        synchronized(reentrantReadWriteLock->theLock,{
                            while (reentrantReadWriteLock->nbRead>0 || reentrantReadWriteLock->isThereWrite){
                                reentrantReadWriteLock->theLock->wait();
                            }
                            reentrantReadWriteLock->writeAdded();
                        })
                    }

                    virtual jbool tryLock(){
                        synchronized(reentrantReadWriteLock->theLock,{
                            if (!reentrantReadWriteLock->isThereWrite && reentrantReadWriteLock->nbRead==0){
                                reentrantReadWriteLock->writeAdded();
                                return true;
                            }
                            return false;
                        })
                    }

                    virtual jbool tryLock(jlong l){
                        synchronized(reentrantReadWriteLock->theLock,{
                            while (l>0 && (reentrantReadWriteLock->nbRead>0 || reentrantReadWriteLock->isThereWrite)){
                                jlong l1=JSystem::currentTimeMillis();
                                reentrantReadWriteLock->theLock->wait(l);
                                l1=JSystem::currentTimeMillis()-l1;
                                l-=l1;
                            }
                            if (!reentrantReadWriteLock->isThereWrite && reentrantReadWriteLock->nbRead==0){
                                reentrantReadWriteLock->writeAdded();
                                return true;
                            }
                            return false;
                        })
                    }

                    virtual void unlock(){
                        synchronized(reentrantReadWriteLock->theLock,{
                            reentrantReadWriteLock->writeRemoved();
                            reentrantReadWriteLock->theLock->notifyAll();
                        })
                    }

                    virtual JCondition* newCondition(){
                        return new JReadWriteLockConditionObject(reentrantReadWriteLock);
                    }

                    virtual ~JWriteLock(){
                    }
                };

                JLock* JReentrantReadWriteLock::writeLock(){
                    return new JWriteLock(this);
                }

                JReentrantReadWriteLock::~JReentrantReadWriteLock(){
                }
            }
        }
    }
}

