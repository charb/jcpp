#ifndef JCPP_LANG_JILLEGAL_THREAD_STATE_EXCEPTION_H
#define JCPP_LANG_JILLEGAL_THREAD_STATE_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.IllegalThreadStateException", simpleName="IllegalThreadStateException");
        class JCPP_EXPORT JIllegalThreadStateException : public JIllegalArgumentException{
        private:
        	static const jlong serialVersionUID = -7626246362397460174LL;

        protected:
            JIllegalThreadStateException(jcpp::lang::JClass* _class);

        public:
            JIllegalThreadStateException();

            JIllegalThreadStateException(JString* message);

            JIllegalThreadStateException(JString* message,JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JIllegalThreadStateException();
        };
    }
}

#endif
