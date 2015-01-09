#ifndef JCPP_UTIL_CONCURRENT_JBROKEN_BARRIER_EXCEPTION_H
#define JCPP_UTIL_CONCURRENT_JBROKEN_BARRIER_EXCEPTION_H

#include "jcpp/lang/JException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.BrokenBarrierException", simpleName="BrokenBarrierException");
            class JCPP_EXPORT JBrokenBarrierException : public JException{
            private:
            	static const jlong serialVersionUID = 7117394618823254244LL;

            protected:
                JBrokenBarrierException(jcpp::lang::JClass* _class);

            public:
                JBrokenBarrierException();

                JBrokenBarrierException(JString* message);

                JBrokenBarrierException(JString* message,JThrowable*cause);

                static jcpp::lang::JClass* getClazz();

                virtual ~JBrokenBarrierException();
            };
        }
    }
}
#endif
