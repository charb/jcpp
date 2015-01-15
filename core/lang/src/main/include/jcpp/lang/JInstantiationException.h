#ifndef JCPP_LANG_JINSTANTIATIONEXCEPTION_H
#define JCPP_LANG_JINSTANTIATIONEXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.InstantiationException", simpleName="InstantiationException");
        class JCPP_EXPORT JInstantiationException : public JReflectiveOperationException{
        private:
        	static const jlong serialVersionUID = -8441929162975509110LL;

        public:
            JInstantiationException();

            JInstantiationException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JInstantiationException();
        };
    }
}

#endif
