#ifndef JCPP_LANG_JNUMBER_FORMAT_EXCEPTION_H
#define JCPP_LANG_JNUMBER_FORMAT_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JNumberFormatException : public JIllegalArgumentException{
        protected:
            JNumberFormatException(jcpp::lang::JClass* _class);

        public:
            JNumberFormatException();

            JNumberFormatException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNumberFormatException();
        };
    }
}

#endif
