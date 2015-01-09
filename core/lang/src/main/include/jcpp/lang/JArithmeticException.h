#ifndef JCPP_LANG_JARITHMETIC_EXCEPTION_H
#define JCPP_LANG_JARITHMETIC_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JArithmeticException : public JRuntimeException{
        public:

            JArithmeticException();

            JArithmeticException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JArithmeticException();
        };
    }
}

#endif
