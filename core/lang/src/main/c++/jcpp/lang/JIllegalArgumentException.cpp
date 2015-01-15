#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalArgumentException::JIllegalArgumentException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JIllegalArgumentException::JIllegalArgumentException():JRuntimeException(getClazz()){
        }

        JIllegalArgumentException::JIllegalArgumentException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JIllegalArgumentException::JIllegalArgumentException(JString* message,JThrowable* cause):JRuntimeException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JIllegalArgumentException::~JIllegalArgumentException(){
        }
    }
}

