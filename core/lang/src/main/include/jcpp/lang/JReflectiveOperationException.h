#ifndef JCPP_LANG_JREFLECTIVE_OPERATION_EXCEPTION_H
#define JCPP_LANG_JREFLECTIVE_OPERATION_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JReflectiveOperationException : public JException{
        protected:
            JReflectiveOperationException(jcpp::lang::JClass* _class);

        public:
            JReflectiveOperationException();

            JReflectiveOperationException(JString* message);

            JReflectiveOperationException(JString* message,JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JReflectiveOperationException();
        };
    }
}

#endif
