#ifndef JCPP_LANG_JUNSUPPORTEDOPERATIONEXCEPTION_H
#define JCPP_LANG_JUNSUPPORTEDOPERATIONEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.UnsupportedOperationException", simpleName="UnsupportedOperationException");
        class JCPP_EXPORT JUnsupportedOperationException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = -1242599979055084673LL;

        protected:
            JUnsupportedOperationException(jcpp::lang::JClass* _class);
        public:
            JUnsupportedOperationException();

            JUnsupportedOperationException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JUnsupportedOperationException();
        };
    }
}

#endif
