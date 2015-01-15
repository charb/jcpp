#include "jcpp/lang/JIllegalAccessException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalAccessException::JIllegalAccessException():JReflectiveOperationException(getClazz()){
        }

        JIllegalAccessException::JIllegalAccessException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
        }

        JIllegalAccessException::~JIllegalAccessException(){
        }
    }
}

