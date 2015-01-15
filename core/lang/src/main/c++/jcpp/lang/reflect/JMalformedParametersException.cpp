#include "jcpp/lang/reflect/JMalformedParametersException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{

            JMalformedParametersException::JMalformedParametersException():JRuntimeException(getClazz()){
            }

            JMalformedParametersException::JMalformedParametersException(JString* message):JRuntimeException(getClazz()){
                setMessage(message);
            }

            JMalformedParametersException::~JMalformedParametersException(){
            }
        }
    }
}
