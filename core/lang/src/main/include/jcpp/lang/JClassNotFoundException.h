#ifndef JCPP_LANG_JCLASSNOTFOUNDEXCEPTION_H
#define JCPP_LANG_JCLASSNOTFOUNDEXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
    	class JClassNotFoundExceptionClass;

    	// @Class(canonicalName="java.lang.ClassNotFoundException", simpleName="ClassNotFoundException");
        class JCPP_EXPORT JClassNotFoundException : public JReflectiveOperationException{
        private:
        	static const jlong serialVersionUID = 9176873029745254542LL;

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
