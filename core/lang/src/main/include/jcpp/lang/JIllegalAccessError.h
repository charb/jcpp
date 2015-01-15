#ifndef JCPP_LANG_ILLEGAL_ACCESS_ERROR_H
#define JCPP_LANG_ILLEGAL_ACCESS_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JIncompatibleClassChangeError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.IllegalAccessError", simpleName="IllegalAccessError");
        class JCPP_EXPORT JIllegalAccessError : public JIncompatibleClassChangeError {
        private:
        	static const jlong serialVersionUID = -8988904074992417891LL;

        protected:
            JIllegalAccessError(jcpp::lang::JClass* _class);

        public:
            JIllegalAccessError();

            JIllegalAccessError(JString* message);

            JIllegalAccessError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JIllegalAccessError();
        };
    }
}

#endif
