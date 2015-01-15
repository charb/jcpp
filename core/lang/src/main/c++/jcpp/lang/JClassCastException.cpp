#include "jcpp/lang/JClassCastException.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JClassCastException::JClassCastException():JRuntimeException(getClazz()){
        }

        JClassCastException::JClassCastException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JClassCastException::~JClassCastException(){
        }
    }
}
