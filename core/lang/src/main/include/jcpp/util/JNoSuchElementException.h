#ifndef JCPP_UTIL_JNOSUCHELEMENTEXCEPTION_H
#define JCPP_UTIL_JNOSUCHELEMENTEXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JNoSuchElementException : public JRuntimeException{

        public:
            JNoSuchElementException();

            JNoSuchElementException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNoSuchElementException();
        };
    }
}

#endif
