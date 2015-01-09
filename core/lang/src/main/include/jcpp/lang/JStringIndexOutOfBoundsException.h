#ifndef JCPP_LANG_JSTRING_INDEXOUTOFBOUNDSEXCEPTION_H
#define JCPP_LANG_JSTRING_INDEXOUTOFBOUNDSEXCEPTION_H

#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JStringIndexOutOfBoundsException : public JIndexOutOfBoundsException{
        protected:
            JStringIndexOutOfBoundsException(jcpp::lang::JClass* _class);

        public:
            JStringIndexOutOfBoundsException();

            JStringIndexOutOfBoundsException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JStringIndexOutOfBoundsException();
        };
    }
}

#endif
