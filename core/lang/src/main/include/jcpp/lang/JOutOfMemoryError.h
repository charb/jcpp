#ifndef JCPP_LANG_JOUT_OF_MEMORY_ERROR_H
#define JCPP_LANG_JOUT_OF_MEMORY_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVirtualMachineError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.OutOfMemoryError", simpleName="OutOfMemoryError");
        class JCPP_EXPORT JOutOfMemoryError : public JVirtualMachineError {
        private:
        	static const jlong serialVersionUID = 8228564086184010517LL;

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
