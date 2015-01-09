#ifndef JCPP_UTIL_CONCURRENT_JTIMEOUT_EXCEPTION_H
#define JCPP_UTIL_CONCURRENT_JTIMEOUT_EXCEPTION_H

#include "jcpp/lang/JException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.TimeoutException", simpleName="TimeoutException");
            class JCPP_EXPORT JTimeoutException : public JException{
            private:
            	static const jlong serialVersionUID = 1900926677490660714LL;

            protected:
                JTimeoutException(jcpp::lang::JClass* _class);

            public:
                JTimeoutException();

                JTimeoutException(JString* message);

                JTimeoutException(JString* message,JThrowable*cause);

                static jcpp::lang::JClass* getClazz();

                virtual ~JTimeoutException();
            };
        }
    }
}
#endif
