#ifndef JCPP_UTIL_JNOSUCHELEMENTEXCEPTION_H
#define JCPP_UTIL_JNOSUCHELEMENTEXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.NoSuchElementException", simpleName="NoSuchElementException");
        class JCPP_EXPORT JNoSuchElementException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = 6769829250639411880LL;

        public:
            JNoSuchElementException();

            JNoSuchElementException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNoSuchElementException();
        };
    }
}

#endif
