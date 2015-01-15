#ifndef JCPP_LANG_JASSERTION_ERROR_H
#define JCPP_LANG_JASSERTION_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.AssertionError", simpleName="AssertionError");
        class JCPP_EXPORT JAssertionError : public JError {
        private:
        	static const jlong serialVersionUID = -5013299493970297370LL;

        protected:
            JAssertionError(jcpp::lang::JClass* _class);

        public:
            JAssertionError();

            JAssertionError(JString* message);

            JAssertionError(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JAssertionError();
        };
    }
}

#endif
