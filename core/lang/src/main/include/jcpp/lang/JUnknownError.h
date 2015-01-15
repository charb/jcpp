#ifndef JCPP_LANG_JUNKNOWN_ERROR_H
#define JCPP_LANG_JUNKNOWN_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVirtualMachineError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.UnknownError", simpleName="UnknownError");
        class JCPP_EXPORT JUnknownError : public JVirtualMachineError {
        private:
        	static const jlong serialVersionUID = 2524784860676771849LL;

        protected:
            JUnknownError(jcpp::lang::JClass* _class);

        public:
            JUnknownError();

            JUnknownError(JString* message);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JUnknownError();
        };
    }
}

#endif
