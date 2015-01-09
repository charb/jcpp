#ifndef JCPP_LANG_JINTERNALERROR_H
#define JCPP_LANG_JINTERNALERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVirtualMachineError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JInternalError : public JVirtualMachineError {
        protected:
            JInternalError(jcpp::lang::JClass* _class);

        public:
            JInternalError();

            JInternalError(JString* message);

            JInternalError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JInternalError();
        };
    }
}

#endif
