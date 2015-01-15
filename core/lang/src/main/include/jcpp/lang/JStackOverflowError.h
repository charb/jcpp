#ifndef JCPP_LANG_JSTACK_OVERFLOW_ERROR_H
#define JCPP_LANG_JSTACK_OVERFLOW_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVirtualMachineError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.StackOverflowError", simpleName="StackOverflowError");
        class JCPP_EXPORT JStackOverflowError : public JVirtualMachineError {
        private:
        	static const jlong serialVersionUID = 8609175038441759607LL;

        protected:
            JStackOverflowError(jcpp::lang::JClass* _class);

        public:
            JStackOverflowError();

            JStackOverflowError(JString* message);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JStackOverflowError();
        };
    }
}

#endif
