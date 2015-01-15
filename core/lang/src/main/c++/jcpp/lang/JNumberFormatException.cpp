#include "jcpp/lang/JNumberFormatException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNumberFormatException::JNumberFormatException(jcpp::lang::JClass* _class):JIllegalArgumentException(_class){
        }

        JNumberFormatException::JNumberFormatException():JIllegalArgumentException(getClazz()){
        }

        JNumberFormatException::JNumberFormatException(JString* message):JIllegalArgumentException(getClazz()){
            setMessage(message);
        }

        JNumberFormatException::~JNumberFormatException(){
        }
    }
}

