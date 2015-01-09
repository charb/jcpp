#ifndef JCPP_LANG_JINDEXOUTOFBOUNDSEXCEPTION_H
#define JCPP_LANG_JINDEXOUTOFBOUNDSEXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JIndexOutOfBoundsException : public JRuntimeException{
        protected:
            JIndexOutOfBoundsException(jcpp::lang::JClass* _class);

        public:
            JIndexOutOfBoundsException();

            JIndexOutOfBoundsException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JIndexOutOfBoundsException();
        };
    }
}

#endif
