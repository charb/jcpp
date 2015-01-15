#ifndef JCPP_LANG_JSECURITY_EXCEPTION_H
#define JCPP_LANG_JSECURITY_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.SecurityException", simpleName="SecurityException");
        class JCPP_EXPORT JSecurityException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = 6878364983674394167LL;

        protected:
            JSecurityException(jcpp::lang::JClass* _class);

        public:
            JSecurityException();

            JSecurityException(JString* message);

            JSecurityException(JString* message,JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JSecurityException();
        };
    }
}

#endif
