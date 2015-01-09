#ifndef JCPP_LANG_JILLEGAL_ACCESS_EXCEPTION_H
#define JCPP_LANG_JILLEGAL_ACCESS_EXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JIllegalAccessException : public JReflectiveOperationException{
        public:
            JIllegalAccessException();

            JIllegalAccessException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JIllegalAccessException();
        };
    }
}

#endif
