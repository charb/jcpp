#include "jcpp/lang/reflect/JMalformedParameterizedTypeException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{

            JMalformedParameterizedTypeException::JMalformedParameterizedTypeException():JRuntimeException(getClazz()){
            }

            JMalformedParameterizedTypeException::JMalformedParameterizedTypeException(JString* message):JRuntimeException(getClazz()){
                setMessage(message);
            }

            JMalformedParameterizedTypeException::~JMalformedParameterizedTypeException(){
            }
        }
    }
}
