#ifndef JCPP_LANG_JARITHMETIC_EXCEPTION_H
#define JCPP_LANG_JARITHMETIC_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.ArithmeticException", simpleName="ArithmeticException");
        class JCPP_EXPORT JArithmeticException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = 2256477558314496007LL;

        public:
            JArithmeticException();

            JArithmeticException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JArithmeticException();
        };
    }
}

#endif
