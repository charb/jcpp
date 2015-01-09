#ifndef JCPP_LANG_JILLEGALARGUMENTEXCEPTION_H
#define JCPP_LANG_JILLEGALARGUMENTEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JIllegalArgumentException : public JRuntimeException{
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
