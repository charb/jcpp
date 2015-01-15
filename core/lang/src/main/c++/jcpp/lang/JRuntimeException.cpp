#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JRuntimeException::JRuntimeException():JException(getClazz()){
        }

        JRuntimeException::JRuntimeException(jcpp::lang::JClass* _class):JException(_class){
        }

        JRuntimeException::JRuntimeException(JString* message):JException(getClazz()){
            setMessage(message);
        }

        JRuntimeException::JRuntimeException(JString* message,JThrowable* cause):JException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JRuntimeException::~JRuntimeException(){
        }
    }
}

