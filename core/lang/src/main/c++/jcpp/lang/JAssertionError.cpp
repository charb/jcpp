#include "jcpp/lang/JAssertionError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JAssertionError::JAssertionError():JError(getClazz()){
        }

        JAssertionError::JAssertionError(jcpp::lang::JClass* _class):JError(_class){
        }

        JAssertionError::JAssertionError(JString* message):JError(getClazz()){
            this->message = message;
        }

        JAssertionError::JAssertionError(JString* message, JThrowable *cause):JError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JAssertionError::~JAssertionError(){
        }
    }
}

