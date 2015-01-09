#ifndef JCPP_LANG_JOUT_OF_MEMORY_ERROR_H
#define JCPP_LANG_JOUT_OF_MEMORY_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVirtualMachineError.h"

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JOutOfMemoryError : public JVirtualMachineError {
        protected:
            JOutOfMemoryError(jcpp::lang::JClass* _class);

        public:
            JOutOfMemoryError();

            JOutOfMemoryError(JString* message);

            JOutOfMemoryError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JOutOfMemoryError();
        };
    }
}

#endif
