#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JInstantiationException::JInstantiationException():JReflectiveOperationException(getClazz()){
        }

        JInstantiationException::JInstantiationException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
        }

        JInstantiationException::~JInstantiationException(){
        }
    }
}

