#ifndef JCPP_LANG_JRUNTIMEEXCEPTION_H
#define JCPP_LANG_JRUNTIMEEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.RuntimeException", simpleName="RuntimeException");
        class JCPP_EXPORT JRuntimeException : public JException{
        private:
        	static const jlong serialVersionUID = -7034897190745766939LL;

        protected:
            JRuntimeException(jcpp::lang::JClass* _class);

        public:
            JRuntimeException();

            JRuntimeException(JString* message);

            JRuntimeException(JString* message,JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JRuntimeException();
        };
    }
}

#endif
