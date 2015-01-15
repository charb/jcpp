#ifndef JCPP_LANG_JNOSUCHFIELDEXCEPTION_H
#define JCPP_LANG_JNOSUCHFIELDEXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.NoSuchFieldException", simpleName="NoSuchFieldException");
        class JCPP_EXPORT JNoSuchFieldException : public JReflectiveOperationException{
        private:
        	static const jlong serialVersionUID = -6143714805279938260LL;

        public:
            JNoSuchFieldException();

            JNoSuchFieldException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNoSuchFieldException();
        };
    }
}

#endif
