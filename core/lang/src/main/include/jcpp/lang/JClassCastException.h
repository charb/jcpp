#ifndef JCPP_LANG_JCLASSCASTEXCEPTION_H
#define JCPP_LANG_JCLASSCASTEXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.ClassCastException", simpleName="ClassCastException");
        class JCPP_EXPORT JClassCastException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = -9223365651070458532LL;

        public:
            JClassCastException();

            JClassCastException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JClassCastException();
        };
    }
}

#endif
