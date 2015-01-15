#ifndef JCPP_LANG_REFLECT_JUNDECLARED_THROWABLE_EXCEPTION_H
#define JCPP_LANG_REFLECT_JUNDECLARED_THROWABLE_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"

namespace jcpp{
    namespace lang{
    	namespace reflect{

    		// @Class(canonicalName="java.lang.reflect.UndeclaredThrowableException", simpleName="UndeclaredThrowableException");
	        class JCPP_EXPORT JUndeclaredThrowableException : public JRuntimeException{
	        private:
	        	static const jlong serialVersionUID = 330127114055056639LL;

	        protected:
	        	JThrowable* undeclaredThrowable;

	        public:
	            JUndeclaredThrowableException();

	            JUndeclaredThrowableException(JThrowable* undeclaredThrowable);

	            JUndeclaredThrowableException(JThrowable* undeclaredThrowable,JString* message);

	            static jcpp::lang::JClass* getClazz();

	            virtual JThrowable* getUndeclaredThrowable();

	            virtual ~JUndeclaredThrowableException();
	        };
	    }
    }
}

#endif
