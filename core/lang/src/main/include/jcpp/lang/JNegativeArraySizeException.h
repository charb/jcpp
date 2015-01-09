#ifndef JCPP_LANG_JNEGATIVE_ARRAY_SIZE_EXCEPTION_H
#define JCPP_LANG_JNEGATIVE_ARRAY_SIZE_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JNegativeArraySizeException : public JRuntimeException{
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
