#include "jcpp/lang/JNoSuchFieldException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNoSuchFieldException::JNoSuchFieldException():JReflectiveOperationException(getClazz()){
        }

        JNoSuchFieldException::JNoSuchFieldException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
        }

        JNoSuchFieldException::~JNoSuchFieldException(){
        }
    }
}
