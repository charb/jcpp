#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalStateException::JIllegalStateException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JIllegalStateException::JIllegalStateException():JRuntimeException(getClazz()){
        }

        JIllegalStateException::JIllegalStateException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JIllegalStateException::~JIllegalStateException(){
        }
    }
}


