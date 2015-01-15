#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JReflectiveOperationException::JReflectiveOperationException():JException(getClazz()){
        }

        JReflectiveOperationException::JReflectiveOperationException(jcpp::lang::JClass* _class):JException(_class){
        }

        JReflectiveOperationException::JReflectiveOperationException(JString* message):JException(getClazz()){
            setMessage(message);
        }

        JReflectiveOperationException::JReflectiveOperationException(JString* message,JThrowable* cause):JException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JReflectiveOperationException::~JReflectiveOperationException(){
        }
    }
}

