#ifndef JCPP_LANG_NOSUCH_METHOD_ERROR_H
#define JCPP_LANG_NOSUCH_METHOD_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JIncompatibleClassChangeError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JNoSuchMethodError : public JIncompatibleClassChangeError {
        protected:
            JNoSuchMethodError(jcpp::lang::JClass* _class);

        public:
            JNoSuchMethodError();

            JNoSuchMethodError(JString* message);

            JNoSuchMethodError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JNoSuchMethodError();
        };
    }
}

#endif
