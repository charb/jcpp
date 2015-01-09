#ifndef JCPP_LANG_JNOSUCHFIELDEXCEPTION_H
#define JCPP_LANG_JNOSUCHFIELDEXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JNoSuchFieldException : public JReflectiveOperationException{
        public:
            JNoSuchFieldException();

            JNoSuchFieldException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNoSuchFieldException();
        };
    }
}

#endif
