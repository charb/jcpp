#ifndef JCPP_LANG_JENUM_CONSTANT_NOT_PRESENT_EXCEPTION_H
#define JCPP_LANG_JENUM_CONSTANT_NOT_PRESENT_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{
    	class JEnumConstantNotPresentExceptionClass;

        class JCPP_EXPORT JEnumConstantNotPresentException : public JRuntimeException{
        protected:
            jcpp::lang::JClass* enumType;
            JString* constantName;
            friend class JEnumConstantNotPresentExceptionClass;

            JEnumConstantNotPresentException();
            
        public:

            JEnumConstantNotPresentException(jcpp::lang::JClass* enumType, JString* constantName);

            static jcpp::lang::JClass* getClazz();

            virtual jcpp::lang::JClass* getEnumType();

            virtual JString* getConstantName();

            virtual ~JEnumConstantNotPresentException();
        };
    }
}

#endif
