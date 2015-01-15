#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNoSuchMethodException::JNoSuchMethodException():JReflectiveOperationException(getClazz()){
        }

        JNoSuchMethodException::JNoSuchMethodException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
        }

        JNoSuchMethodException::~JNoSuchMethodException(){
        }
    }
}

