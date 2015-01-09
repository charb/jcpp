#ifndef JCPP_LANG_JNOSUCHMETHODEXCEPTION_H
#define JCPP_LANG_JNOSUCHMETHODEXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JNoSuchMethodException : public JReflectiveOperationException{
        public:
            JNoSuchMethodException();

            JNoSuchMethodException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNoSuchMethodException();
        };
    }
}

#endif
