#include "jcpp/lang/JInstantiationError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JInstantiationError::JInstantiationError():JIncompatibleClassChangeError(getClazz()){
        }

        JInstantiationError::JInstantiationError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JInstantiationError::JInstantiationError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
        }

        JInstantiationError::JInstantiationError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JInstantiationError::~JInstantiationError(){
        }
    }
}

