#ifndef JCPP_LANG_REFLECT_JMALFORMED_PARAMETERIZED_TYPE_EXCEPTION_H
#define JCPP_LANG_REFLECT_JMALFORMED_PARAMETERIZED_TYPE_EXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{
    	namespace reflect{
	        class JCPP_EXPORT JMalformedParameterizedTypeException : public JRuntimeException{
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
