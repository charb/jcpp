#ifndef JCPP_LANG_JCLASSNOTFOUNDEXCEPTION_H
#define JCPP_LANG_JCLASSNOTFOUNDEXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
    	class JClassNotFoundExceptionClass;

        class JCPP_EXPORT JClassNotFoundException : public JReflectiveOperationException{
        protected:
        	JThrowable* ex;
        	friend class JClassNotFoundExceptionClass;

        public:
            JClassNotFoundException();

            JClassNotFoundException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual void setCause(JThrowable* th); 

            virtual JThrowable* getException();

			virtual JThrowable* getCause();            

            virtual ~JClassNotFoundException();
        };
    }
}

#endif
