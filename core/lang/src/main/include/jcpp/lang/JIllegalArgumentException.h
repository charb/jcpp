#ifndef JCPP_LANG_JILLEGALARGUMENTEXCEPTION_H
#define JCPP_LANG_JILLEGALARGUMENTEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.IllegalArgumentException", simpleName="IllegalArgumentException");
        class JCPP_EXPORT JIllegalArgumentException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = -5365630128856068164LL;

        protected:
            JIllegalArgumentException(jcpp::lang::JClass* _class);

        public:
            JIllegalArgumentException();

            JIllegalArgumentException(JString* message);

            JIllegalArgumentException(JString* message,JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JIllegalArgumentException();
        };
    }
}

#endif
