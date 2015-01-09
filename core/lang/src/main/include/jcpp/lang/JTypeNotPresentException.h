#ifndef JCPP_LANG_JTYPE_NOT_PRESENT_EXCEPTION_H
#define JCPP_LANG_JTYPE_NOT_PRESENT_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
    	class JTypeNotPresentExceptionClass;

        class JCPP_EXPORT JTypeNotPresentException : public JRuntimeException{
        protected:
            JTypeNotPresentException(jcpp::lang::JClass* _class);
            JString* typeName;
            friend class JTypeNotPresentExceptionClass;

        public:
            JTypeNotPresentException();

            JTypeNotPresentException(JString* typeName, JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual JString* getTypeName();

            virtual ~JTypeNotPresentException();
        };
    }
}

#endif
