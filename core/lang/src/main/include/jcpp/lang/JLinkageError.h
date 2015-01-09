#ifndef JCPP_LANG_JLINKAGEERROR_H
#define JCPP_LANG_JLINKAGEERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JLinkageError : public JError {
        protected:
            JLinkageError(jcpp::lang::JClass* _class);

        public:
            JLinkageError();

            JLinkageError(JString* message);

            JLinkageError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JLinkageError();
        };
    }
}

#endif
