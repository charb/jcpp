#ifndef JCPP_LANG_JCLONENOTSUPPORTEDEXCEPTION_H
#define JCPP_LANG_JCLONENOTSUPPORTEDEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.CloneNotSupportedException", simpleName="CloneNotSupportedException");
        class JCPP_EXPORT JCloneNotSupportedException : public JException{
        private:
        	static const jlong serialVersionUID = 5195511250079656443LL;

        protected:
            JCloneNotSupportedException(jcpp::lang::JClass* _class);

        public:
            JCloneNotSupportedException();

            JCloneNotSupportedException(JString* message);

            JCloneNotSupportedException(JString* message,JThrowable* cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JCloneNotSupportedException();
        };
    }
}

#endif
