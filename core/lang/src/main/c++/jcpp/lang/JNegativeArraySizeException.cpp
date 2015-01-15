#include "jcpp/lang/JNegativeArraySizeException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNegativeArraySizeException::JNegativeArraySizeException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JNegativeArraySizeException::JNegativeArraySizeException():JRuntimeException(getClazz()){
        }

        JNegativeArraySizeException::JNegativeArraySizeException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JNegativeArraySizeException::JNegativeArraySizeException(JString* message,JThrowable* cause):JRuntimeException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JNegativeArraySizeException::~JNegativeArraySizeException(){
        }
    }
}

