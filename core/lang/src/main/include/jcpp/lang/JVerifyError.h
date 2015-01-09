#ifndef JCPP_LANG_JVERIFYERROR_H
#define JCPP_LANG_JVERIFYERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JVerifyError : public JLinkageError {
        protected:
            JVerifyError(jcpp::lang::JClass* _class);

        public:
            JVerifyError();

            JVerifyError(JString* message);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JVerifyError();
        };
    }
}

#endif
