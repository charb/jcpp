#ifndef JCPP_UTIL_CONCURRENT_LOCKS_REENTRANT_READWRITE_LOCK_H
#define JCPP_UTIL_CONCURRENT_LOCKS_REENTRANT_READWRITE_LOCK_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/concurrent/locks/JLock.h"
#include "jcpp/util/concurrent/locks/JReadWriteLock.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace locks{

            	// @Class(canonicalName="java.util.concurrent.ReentrantReadWriteLock", simpleName="ReentrantReadWriteLock");
                class JCPP_EXPORT JReentrantReadWriteLock : public JObject, public JReadWriteLock{
                    jint nbRead;
                    jbool isThereWrite;
                    JObject* theLock;
                    void incrementRead();
                    void decrementRead();
                    void writeAdded();
                    void writeRemoved();
                    friend class JReadLock;
                    friend class JWriteLock;
                    friend class JReadWriteLockConditionObject;

                public:
                    JReentrantReadWriteLock();

                    static JClass* getClazz();

                    virtual JLock* readLock();

                    virtual JLock* writeLock();

                    virtual ~JReentrantReadWriteLock();
                };
            }
        }
    }
}

#endif
