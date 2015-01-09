#ifndef JCPP_LANG_JNULLPOINTEREXCEPTION_H
#define JCPP_LANG_JNULLPOINTEREXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JNullPointerException : public JRuntimeException{

        public:
            JNullPointerException();

            JNullPointerException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNullPointerException();
        };
    }
}

#endif
