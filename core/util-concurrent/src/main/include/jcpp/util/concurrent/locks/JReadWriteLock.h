#ifndef JCPP_UTIL_CONCURRENT_LOCKS_READWRITE_LOCK_H
#define JCPP_UTIL_CONCURRENT_LOCKS_READWRITE_LOCK_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/concurrent/locks/JLock.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace locks{

            	// @Class(canonicalName="java.util.concurrent.ReadWriteLock", simpleName="ReadWriteLock");
                class JCPP_EXPORT JReadWriteLock : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual JLock* readLock()=0;

                    virtual JLock* writeLock()=0;

                    virtual ~JReadWriteLock();
                };
            }
        }
    }
}

#endif
