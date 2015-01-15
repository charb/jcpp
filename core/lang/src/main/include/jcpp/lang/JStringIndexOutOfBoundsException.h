#ifndef JCPP_LANG_JSTRING_INDEXOUTOFBOUNDSEXCEPTION_H
#define JCPP_LANG_JSTRING_INDEXOUTOFBOUNDSEXCEPTION_H

#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.StringIndexOutOfBoundsException", simpleName="StringIndexOutOfBoundsException");
        class JCPP_EXPORT JStringIndexOutOfBoundsException : public JIndexOutOfBoundsException{
        private:
        	static const jlong serialVersionUID = -6762910422159637258LL;

        protected:
            JStringIndexOutOfBoundsException(jcpp::lang::JClass* _class);

        public:
            JStringIndexOutOfBoundsException();

            JStringIndexOutOfBoundsException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JStringIndexOutOfBoundsException();
        };
    }
}

#endif
