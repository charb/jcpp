#ifndef JCPP_LANG_JNUMBER_FORMAT_EXCEPTION_H
#define JCPP_LANG_JNUMBER_FORMAT_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.NumberFormatException", simpleName="NumberFormatException");
        class JCPP_EXPORT JNumberFormatException : public JIllegalArgumentException{
        private:
        	static const jlong serialVersionUID = -2848938806368998894LL;

        protected:
            JNumberFormatException(jcpp::lang::JClass* _class);

        public:
            JNumberFormatException();

            JNumberFormatException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNumberFormatException();
        };
    }
}

#endif
