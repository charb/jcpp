#ifndef JCPP_LANG_ABSTRACT_METHOD_ERROR_H
#define JCPP_LANG_ABSTRACT_METHOD_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JIncompatibleClassChangeError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JAbstractMethodError : public JIncompatibleClassChangeError {
        protected:
            JAbstractMethodError(jcpp::lang::JClass* _class);

        public:
            JAbstractMethodError();

            JAbstractMethodError(JString* message);

            JAbstractMethodError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JAbstractMethodError();
        };
    }
}

#endif
