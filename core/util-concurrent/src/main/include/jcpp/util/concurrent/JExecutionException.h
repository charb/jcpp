#ifndef JCPP_UTIL_CONCURRENT_JEXECUTION_EXCEPTION_H
#define JCPP_UTIL_CONCURRENT_JEXECUTION_EXCEPTION_H

#include "jcpp/lang/JException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.ExecutionException", simpleName="ExecutionException");
            class JCPP_EXPORT JExecutionException : public JException{
            private:
            	static const jlong serialVersionUID = 7830266012832686185LL;

            protected:
                JExecutionException(jcpp::lang::JClass* _class);

            public:
                JExecutionException();

                JExecutionException(JString* message);

                JExecutionException(JString* message,JThrowable*cause);

                static jcpp::lang::JClass* getClazz();

                virtual ~JExecutionException();
            };
        }
    }
}
#endif
