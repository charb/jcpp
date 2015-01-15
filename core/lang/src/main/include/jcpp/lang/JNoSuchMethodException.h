#ifndef JCPP_LANG_JNOSUCHMETHODEXCEPTION_H
#define JCPP_LANG_JNOSUCHMETHODEXCEPTION_H

#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.NoSuchMethodException", simpleName="NoSuchMethodException");
        class JCPP_EXPORT JNoSuchMethodException : public JReflectiveOperationException{
        private:
        	static const jlong serialVersionUID = 5034388446362600923LL;

        public:
            JNoSuchMethodException();

            JNoSuchMethodException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JNoSuchMethodException();
        };
    }
}

#endif
