#ifndef JCPP_UTIL_CONCURRENT_JEXECUTOR_H
#define JCPP_UTIL_CONCURRENT_JEXECUTOR_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JRunnable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.Executor", simpleName="Executor");
            class JCPP_EXPORT JExecutor : public JInterface{
            public:
                static JClass* getClazz();

                virtual void execute(JRunnable* command)=0;

                virtual ~JExecutor();
            };
        }
    }
}

#endif
