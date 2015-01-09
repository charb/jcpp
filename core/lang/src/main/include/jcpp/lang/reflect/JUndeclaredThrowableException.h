#ifndef JCPP_LANG_REFLECT_JUNDECLARED_THROWABLE_EXCEPTION_H
#define JCPP_LANG_REFLECT_JUNDECLARED_THROWABLE_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"

namespace jcpp{
    namespace lang{
    	namespace reflect{
    		class JUndeclaredThrowableExceptionClass;

	        class JCPP_EXPORT JUndeclaredThrowableException : public JRuntimeException{
	        protected:
	        	JThrowable* undeclaredThrowable;
	        	friend class JUndeclaredThrowableExceptionClass;

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
