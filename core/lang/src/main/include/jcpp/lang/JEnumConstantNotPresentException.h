#ifndef JCPP_LANG_JENUM_CONSTANT_NOT_PRESENT_EXCEPTION_H
#define JCPP_LANG_JENUM_CONSTANT_NOT_PRESENT_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.EnumConstantNotPresentException", simpleName="EnumConstantNotPresentException");
        class JCPP_EXPORT JEnumConstantNotPresentException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = -6046998521960521108LL;

        protected:
            jcpp::lang::JClass* enumType;
            JString* constantName;

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
