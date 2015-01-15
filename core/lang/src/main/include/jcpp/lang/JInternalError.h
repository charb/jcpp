#ifndef JCPP_LANG_JINTERNALERROR_H
#define JCPP_LANG_JINTERNALERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVirtualMachineError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.InternalError", simpleName="InternalError");
        class JCPP_EXPORT JInternalError : public JVirtualMachineError {
        private:
        	static const jlong serialVersionUID = -9062593416125562365LL;

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
