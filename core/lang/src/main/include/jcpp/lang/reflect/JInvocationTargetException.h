#ifndef JCPP_LANG_REFLECT_JINVOCATION_TARGET_EXCEPTION_H
#define JCPP_LANG_REFLECT_JINVOCATION_TARGET_EXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"

namespace jcpp{
    namespace lang{
    	namespace reflect{

    		// @Class(canonicalName="java.lang.reflect.InvocationTargetException", simpleName="InvocationTargetException");
	        class JCPP_EXPORT JInvocationTargetException : public JReflectiveOperationException{
	        private:
	        	static const jlong serialVersionUID = 4085088731926701167LL;

	        protected:
	        	JThrowable* target;

	        public:
	            JInvocationTargetException();

	            JInvocationTargetException(JThrowable* target);

	            JInvocationTargetException(JThrowable* target,JString* message);

	            static jcpp::lang::JClass* getClazz();

	            virtual JThrowable* getTargetException();

	            virtual ~JInvocationTargetException();
	        };
	    }
    }
}

#endif
