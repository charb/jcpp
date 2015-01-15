#include "jcpp/lang/JIllegalThreadStateException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalThreadStateException::JIllegalThreadStateException(jcpp::lang::JClass* _class):JIllegalArgumentException(_class){
        }

        JIllegalThreadStateException::JIllegalThreadStateException():JIllegalArgumentException(getClazz()){
        }

        JIllegalThreadStateException::JIllegalThreadStateException(JString* message):JIllegalArgumentException(getClazz()){
            setMessage(message);
        }

        JIllegalThreadStateException::JIllegalThreadStateException(JString* message,JThrowable* cause):JIllegalArgumentException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JIllegalThreadStateException::~JIllegalThreadStateException(){
        }
    }
}

