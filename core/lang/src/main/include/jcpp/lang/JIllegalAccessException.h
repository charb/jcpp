#ifndef JCPP_LANG_JILLEGAL_ACCESS_EXCEPTION_H
#define JCPP_LANG_JILLEGAL_ACCESS_EXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.IllegalAccessException", simpleName="IllegalAccessException");
        class JCPP_EXPORT JIllegalAccessException : public JReflectiveOperationException{
        private:
        	static const jlong serialVersionUID = 6616958222490762034LL;

        public:
            JIllegalAccessException();

            JIllegalAccessException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JIllegalAccessException();
        };
    }
}

#endif
