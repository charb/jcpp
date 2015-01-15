#include "jcpp/lang/JIllegalAccessError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalAccessError::JIllegalAccessError():JIncompatibleClassChangeError(getClazz()){
        }

        JIllegalAccessError::JIllegalAccessError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JIllegalAccessError::JIllegalAccessError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
        }

        JIllegalAccessError::JIllegalAccessError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JIllegalAccessError::~JIllegalAccessError(){
        }
    }
}

