#ifndef JCPP_UTIL_CONCURRENT_LOCKS_CONDITION_H
#define JCPP_UTIL_CONCURRENT_LOCKS_CONDITION_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace locks{

            	// @Class(canonicalName="java.util.concurrent.Condition", simpleName="Condition");
                class JCPP_EXPORT JCondition : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void await()=0;

                    virtual jlong await(jlong l)=0;

                    virtual void signal()=0;

                    virtual void signalAll()=0;

                    virtual ~JCondition();
                };
            }
        }
    }
}

#endif
