#ifndef JCPP_UTIL_CONCURRENT_JREJECTED_EXECUTION_HANDLER_H
#define JCPP_UTIL_CONCURRENT_JREJECTED_EXECUTION_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JThreadPoolExecutor;

            // @Class(canonicalName="java.util.concurrent.RejectedExecutionHandler", simpleName="RejectedExecutionHandler");
            class JCPP_EXPORT JRejectedExecutionHandler : public JInterface{
            public:
                static JClass* getClazz();

                virtual void rejectedExecution(JRunnable* command, JThreadPoolExecutor* executor)=0;

                virtual ~JRejectedExecutionHandler();
            };
        }
    }
}

#endif
