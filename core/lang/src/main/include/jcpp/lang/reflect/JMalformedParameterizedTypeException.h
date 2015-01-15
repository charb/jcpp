#ifndef JCPP_LANG_REFLECT_JMALFORMED_PARAMETERIZED_TYPE_EXCEPTION_H
#define JCPP_LANG_REFLECT_JMALFORMED_PARAMETERIZED_TYPE_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
    	namespace reflect{

    		// @Class(canonicalName="java.lang.reflect.MalformedParameterizedTypeException", simpleName="MalformedParameterizedTypeException");
	        class JCPP_EXPORT JMalformedParameterizedTypeException : public JRuntimeException{
	        private:
	        	static const jlong serialVersionUID = -5696557788586220964LL;

	        public:
	            JMalformedParameterizedTypeException();

	            JMalformedParameterizedTypeException(JString* message);

	            static jcpp::lang::JClass* getClazz();

	            virtual ~JMalformedParameterizedTypeException();
	        };
	    }
    }
}

#endif
