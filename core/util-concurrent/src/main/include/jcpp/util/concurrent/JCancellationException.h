#ifndef JCPP_UTIL_CONCURRENT_JCANCELLATION_EXCEPTION_H
#define JCPP_UTIL_CONCURRENT_JCANCELLATION_EXCEPTION_H

#include "jcpp/lang/JIllegalStateException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.CancellationException", simpleName="CancellationException");
            class JCPP_EXPORT JCancellationException : public JIllegalStateException{
            private:
            	static const jlong serialVersionUID = -9202173006928992231LL;

            protected:
                JCancellationException(jcpp::lang::JClass* _class);

            public:
                JCancellationException();

                JCancellationException(JString* message);

                JCancellationException(JString* message,JThrowable*cause);

                static jcpp::lang::JClass* getClazz();

                virtual ~JCancellationException();
            };
        }
    }
}
#endif
