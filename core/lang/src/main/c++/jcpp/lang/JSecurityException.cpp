#include "jcpp/lang/JSecurityException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        JSecurityException::JSecurityException():JRuntimeException(getClazz()){
        }

        JSecurityException::JSecurityException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JSecurityException::JSecurityException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JSecurityException::JSecurityException(JString* message,JThrowable* cause):JRuntimeException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JSecurityException::~JSecurityException(){
        }
    }
}

