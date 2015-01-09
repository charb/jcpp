#ifndef JCPP_LANG_JILLEGAL_THREAD_STATE_EXCEPTION_H
#define JCPP_LANG_JILLEGAL_THREAD_STATE_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JIllegalThreadStateException : public JIllegalArgumentException{
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
