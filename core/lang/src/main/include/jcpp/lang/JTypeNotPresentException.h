#ifndef JCPP_LANG_JTYPE_NOT_PRESENT_EXCEPTION_H
#define JCPP_LANG_JTYPE_NOT_PRESENT_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.TypeNotPresentException", simpleName="TypeNotPresentException");
        class JCPP_EXPORT JTypeNotPresentException : public JRuntimeException{
    	private:
    		static const jlong serialVersionUID = -5101214195716534496LL;

        protected:
            JTypeNotPresentException(jcpp::lang::JClass* _class);
            JString* typeName;

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
