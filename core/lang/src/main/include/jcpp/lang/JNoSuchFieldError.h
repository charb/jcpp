#ifndef JCPP_LANG_NOSUCH_FIELD_ERROR_H
#define JCPP_LANG_NOSUCH_FIELD_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JIncompatibleClassChangeError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JNoSuchFieldError : public JIncompatibleClassChangeError {
        protected:
            JNoSuchFieldError(jcpp::lang::JClass* _class);

        public:
            JNoSuchFieldError();

            JNoSuchFieldError(JString* message);

            JNoSuchFieldError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JNoSuchFieldError();
        };
    }
}

#endif
