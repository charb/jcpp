#ifndef JCPP_LANG_JARRAYINDEXOUTOFBOUNDSEXCEPTION_H
#define JCPP_LANG_JARRAYINDEXOUTOFBOUNDSEXCEPTION_H

#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JArrayIndexOutOfBoundsException : public JIndexOutOfBoundsException {
        public:
            JArrayIndexOutOfBoundsException();

            JArrayIndexOutOfBoundsException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JArrayIndexOutOfBoundsException();
        };
    }
}
#endif
