#ifndef JCPP_LANG_JSECURITY_EXCEPTION_H
#define JCPP_LANG_JSECURITY_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JSecurityException : public JRuntimeException{
        protected:
            JSecurityException(jcpp::lang::JClass* _class);

        public:
            JSecurityException();

            JSecurityException(JString* message);

            JSecurityException(JString* message,JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JSecurityException();
        };
    }
}

#endif
