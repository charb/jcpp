#ifndef JCPP_UTIL_CONCURRENT_JTHREAD_FACTORY_H
#define JCPP_UTIL_CONCURRENT_JTHREAD_FACTORY_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JThread.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.ThreadFactory", simpleName="ThreadFactory");
            class JCPP_EXPORT JThreadFactory : public JInterface{
            public:
                static JClass* getClazz();

                virtual JThread* newThread(JRunnable* r)=0;

                virtual ~JThreadFactory();
            };
        }
    }
}

#endif
