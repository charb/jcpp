#include "jcpp/lang/JNoSuchFieldError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNoSuchFieldError::JNoSuchFieldError():JIncompatibleClassChangeError(getClazz()){
        }

        JNoSuchFieldError::JNoSuchFieldError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JNoSuchFieldError::JNoSuchFieldError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
        }

        JNoSuchFieldError::JNoSuchFieldError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JNoSuchFieldError::~JNoSuchFieldError(){
        }
    }
}

