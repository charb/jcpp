#ifndef JCPP_LANG_JNULLPOINTEREXCEPTION_H
#define JCPP_LANG_JNULLPOINTEREXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.NullPointerException", simpleName="NullPointerException");
        class JCPP_EXPORT JNullPointerException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = 5162710183389028792LL;

        public:
            JNullPointerException();

            JNullPointerException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNullPointerException();
        };
    }
}

#endif
