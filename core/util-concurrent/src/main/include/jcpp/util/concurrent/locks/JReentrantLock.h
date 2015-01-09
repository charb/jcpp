#ifndef JCPP_UTIL_CONCURRENT_LOCKS_REENTRANT_LOCK_H
#define JCPP_UTIL_CONCURRENT_LOCKS_REENTRANT_LOCK_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/concurrent/locks/JLock.h"
#include "jcpp/util/concurrent/locks/JCondition.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace locks{

            	// @Class(canonicalName="java.util.concurrent.ReentrantLock", simpleName="ReentrantLock");
                class JCPP_EXPORT JReentrantLock : public JObject, public JLock{
                    JObject* theLock;
                    friend class JConditionObject;

                public:
                    JReentrantLock();

                    static JClass* getClazz();

                    virtual void lock();

                    virtual jbool tryLock();

                    virtual jbool tryLock(jlong l);

                    virtual void unlock();

                    virtual JCondition* newCondition();

                    virtual ~JReentrantLock();
                };
            }
        }
    }
}

#endif
