#ifndef JCPP_LANG_ILLEGAL_ACCESS_ERROR_H
#define JCPP_LANG_ILLEGAL_ACCESS_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JIncompatibleClassChangeError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JIllegalAccessError : public JIncompatibleClassChangeError {
        protected:
            JIllegalAccessError(jcpp::lang::JClass* _class);

        public:
            JIllegalAccessError();

            JIllegalAccessError(JString* message);

            JIllegalAccessError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JIllegalAccessError();
        };
    }
}

#endif
