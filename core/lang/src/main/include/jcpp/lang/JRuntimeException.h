#ifndef JCPP_LANG_JRUNTIMEEXCEPTION_H
#define JCPP_LANG_JRUNTIMEEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JRuntimeException : public JException{
        protected:
            JRuntimeException(jcpp::lang::JClass* _class);

        public:
            JRuntimeException();

            JRuntimeException(JString* message);

            JRuntimeException(JString* message,JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JRuntimeException();
        };
    }
}

#endif
