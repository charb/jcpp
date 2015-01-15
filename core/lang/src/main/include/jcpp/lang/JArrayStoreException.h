#ifndef JCPP_LANG_JARRAY_STORE_EXCEPTION_H
#define JCPP_LANG_JARRAY_STORE_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JRuntimeException.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.ArrayStoreException", simpleName="ArrayStoreException");
        class JCPP_EXPORT JArrayStoreException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = -4522193890499838241LL;

        public:

            JArrayStoreException();

            JArrayStoreException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JArrayStoreException();
        };
    }
}

#endif
