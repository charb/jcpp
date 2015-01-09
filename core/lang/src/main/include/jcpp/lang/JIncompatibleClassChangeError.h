#ifndef JCPP_LANG_JINCOMPATIBLE_CLASS_CHANGE_ERROR
#define JCPP_LANG_JINCOMPATIBLE_CLASS_CHANGE_ERROR

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JIncompatibleClassChangeError : public JLinkageError {
        protected:
            JIncompatibleClassChangeError(jcpp::lang::JClass* _class);

        public:
            JIncompatibleClassChangeError();

            JIncompatibleClassChangeError(JString* message);

            JIncompatibleClassChangeError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JIncompatibleClassChangeError();
        };
    }
}

#endif
