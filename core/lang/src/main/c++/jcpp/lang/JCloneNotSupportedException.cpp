#include "jcpp/lang/JCloneNotSupportedException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JCloneNotSupportedException::JCloneNotSupportedException():JException(getClazz()){
        }

        JCloneNotSupportedException::JCloneNotSupportedException(jcpp::lang::JClass* _class):JException(_class){
        }

        JCloneNotSupportedException::JCloneNotSupportedException(JString* message):JException(getClazz()){
            setMessage(message);
        }

        JCloneNotSupportedException::JCloneNotSupportedException(JString* message,JThrowable* cause):JException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JCloneNotSupportedException::~JCloneNotSupportedException(){
        }
    }
}


