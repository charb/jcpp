#ifndef JCPP_LANG_JINDEXOUTOFBOUNDSEXCEPTION_H
#define JCPP_LANG_JINDEXOUTOFBOUNDSEXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.IndexOutOfBoundsException", simpleName="IndexOutOfBoundsException");
        class JCPP_EXPORT JIndexOutOfBoundsException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = 234122996006267687LL;

        protected:
            JIndexOutOfBoundsException(jcpp::lang::JClass* _class);

        public:
            JIndexOutOfBoundsException();

            JIndexOutOfBoundsException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JIndexOutOfBoundsException();
        };
    }
}

#endif
