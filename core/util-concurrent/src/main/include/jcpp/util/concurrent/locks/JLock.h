#ifndef JCPP_UTIL_CONCURRENT_LOCKS_LOCK_H
#define JCPP_UTIL_CONCURRENT_LOCKS_LOCK_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace locks{
                class JCondition;
                
                // @Class(canonicalName="java.util.concurrent.Lock", simpleName="Lock");
                class JCPP_EXPORT JLock : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void lock()=0;

                    virtual jbool tryLock()=0;

                    virtual jbool tryLock(jlong l)=0;

                    virtual void unlock()=0;

                    virtual JCondition* newCondition()=0;

                    virtual ~JLock();
                };
            }
        }
    }
}

#endif
