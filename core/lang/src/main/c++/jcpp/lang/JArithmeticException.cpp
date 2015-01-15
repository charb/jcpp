#include "jcpp/lang/JArithmeticException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JArithmeticException::JArithmeticException():JRuntimeException(getClazz()){
        }

        JArithmeticException::JArithmeticException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JArithmeticException::~JArithmeticException(){
        }
    }
}
