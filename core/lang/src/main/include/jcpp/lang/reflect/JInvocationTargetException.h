#ifndef JCPP_LANG_REFLECT_JINVOCATION_TARGET_EXCEPTION_H
#define JCPP_LANG_REFLECT_JINVOCATION_TARGET_EXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThrowable.h"

namespace jcpp{
    namespace lang{
    	namespace reflect{
    		class JInvocationTargetExceptionClass;

	        class JCPP_EXPORT JInvocationTargetException : public JReflectiveOperationException{
	        protected:
	        	JThrowable* target;
	        	friend class JInvocationTargetExceptionClass;

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
