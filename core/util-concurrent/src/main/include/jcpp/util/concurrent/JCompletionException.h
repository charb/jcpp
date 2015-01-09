#ifndef JCPP_UTIL_CONCURRENT_JCOMPLETION_EXCEPTION_H
#define JCPP_UTIL_CONCURRENT_JCOMPLETION_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.CompletionException", simpleName="CompletionException");
            class JCPP_EXPORT JCompletionException : public JRuntimeException{
            private:
            	static const jlong serialVersionUID = 7830266012832686185LL;

            protected:
                JCompletionException(jcpp::lang::JClass* _class);

            public:
                JCompletionException();

                JCompletionException(JString* message);

                JCompletionException(JString* message,JThrowable*cause);

                static jcpp::lang::JClass* getClazz();

                virtual ~JCompletionException();
            };
        }
    }
}
#endif
