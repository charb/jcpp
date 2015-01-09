#ifndef JCPP_LANG_JILLEGALSTATEEXCEPTION_H
#define JCPP_LANG_JILLEGALSTATEEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JIllegalStateException : public JRuntimeException{
        protected:
            JIllegalStateException(jcpp::lang::JClass* _class);

        public:
            JIllegalStateException();

            JIllegalStateException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JIllegalStateException();
        };
    }
}

#endif
