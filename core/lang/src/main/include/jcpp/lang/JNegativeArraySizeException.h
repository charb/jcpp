#ifndef JCPP_LANG_JNEGATIVE_ARRAY_SIZE_EXCEPTION_H
#define JCPP_LANG_JNEGATIVE_ARRAY_SIZE_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.NegativeArraySizeException", simpleName="NegativeArraySizeException");
        class JCPP_EXPORT JNegativeArraySizeException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = -8960118058596991861LL;

        protected:
            JNegativeArraySizeException(jcpp::lang::JClass* _class);

        public:
            JNegativeArraySizeException();

            JNegativeArraySizeException(JString* message);

            JNegativeArraySizeException(JString* message,JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNegativeArraySizeException();
        };
    }
}

#endif
