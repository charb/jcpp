#ifndef JCPP_LANG_JVIRTUALMACHINEERROR_H
#define JCPP_LANG_JVIRTUALMACHINEERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.VirtualMachineError", simpleName="VirtualMachineError");
        class JCPP_EXPORT JVirtualMachineError : public JError {
        private:
        	static const jlong serialVersionUID = 4161983926571568670LL;

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
