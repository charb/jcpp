#include "jcpp/util/concurrent/locks/JReentrantLock.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInstantiationException.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace locks{

                JReentrantLock::JReentrantLock():JObject(getClazz()){
                    theLock=new JObject();
                }

                //TODO put some protections on which threads locked what
                void JReentrantLock::lock(){
                    theLock->internalLock();
                }

                jbool JReentrantLock::tryLock(){
                    return theLock->internalTryLock();
                }

                jbool JReentrantLock::tryLock(jlong l){
                    return theLock->internalTryLock(l);
                }

                void JReentrantLock::unlock(){
                    theLock->internalUnlock();
                }

                // @Class(canonicalName="java.util.concurrent.ReentrantLock$ConditionObject", simpleName="ReentrantLock$ConditionObject");
                class JConditionObject : public JCondition, public JObject{
                    JReentrantLock* reentrantLock;
                    jbool signaled;

                public:
                    JConditionObject(JReentrantLock* reentrantLock){
                        this->reentrantLock=reentrantLock;
                        this->signaled=false;
                    }

                    static JClass* getClazz();

                    virtual void await(){
                        signaled=false;
                        while (!signaled){
                            reentrantLock->theLock->wait();
                        }
                    }

                    virtual jlong await(jlong l){
                        signaled=false;
                        while (!signaled && l>0){
                            jlong l1=JSystem::currentTimeMillis();
                            reentrantLock->theLock->wait(l);
                            l1=JSystem::currentTimeMillis()-l1;
                            l-=l1;
                        }
                        return (l<0 ? 0 : l);
                    }

                    virtual void signal(){
                        signaled=true;
                        reentrantLock->theLock->notify();
                    }

                    virtual void signalAll(){
                        signaled=true;
                        reentrantLock->theLock->notifyAll();
                    }

                    virtual ~JConditionObject(){
                    }
                };

                JCondition* JReentrantLock::newCondition(){
                    return new JConditionObject(this);
                }

                JReentrantLock::~JReentrantLock(){
                }
            }
        }
    }
}

