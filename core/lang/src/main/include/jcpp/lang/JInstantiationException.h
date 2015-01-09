#ifndef JCPP_LANG_JINSTANTIATIONEXCEPTION_H
#define JCPP_LANG_JINSTANTIATIONEXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JInstantiationException : public JReflectiveOperationException{
        public:
            JInstantiationException();

            JInstantiationException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JInstantiationException();
        };
    }
}

#endif
