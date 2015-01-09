#ifndef JCPP_LANG_JVIRTUALMACHINEERROR_H
#define JCPP_LANG_JVIRTUALMACHINEERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JVirtualMachineError : public JError {
        protected:
            JVirtualMachineError(jcpp::lang::JClass* _class);

        public:
            JVirtualMachineError();

            JVirtualMachineError(JString* message);

            JVirtualMachineError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JVirtualMachineError();
        };
    }
}

#endif
