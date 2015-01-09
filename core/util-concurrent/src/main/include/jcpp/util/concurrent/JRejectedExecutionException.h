#ifndef JCPP_UTIL_CONCURRENT_JREJECTED_EXECUTION_EXCEPTION_H
#define JCPP_UTIL_CONCURRENT_JREJECTED_EXECUTION_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.RejectedExecutionException", simpleName="RejectedExecutionException");
            class JCPP_EXPORT JRejectedExecutionException : public JRuntimeException{
            private:
            	static const jlong serialVersionUID = -375805702767069545LL;

            protected:
                JRejectedExecutionException(jcpp::lang::JClass* _class);

            public:
                JRejectedExecutionException();

                JRejectedExecutionException(JString* message);

                JRejectedExecutionException(JString* message,JThrowable*cause);

                static jcpp::lang::JClass* getClazz();

                virtual ~JRejectedExecutionException();
            };
        }
    }
}
#endif
