#include "jcpp/lang/JAbstractMethodError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JAbstractMethodError::JAbstractMethodError():JIncompatibleClassChangeError(getClazz()){
        }

        JAbstractMethodError::JAbstractMethodError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JAbstractMethodError::JAbstractMethodError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
        }

        JAbstractMethodError::JAbstractMethodError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JAbstractMethodError::~JAbstractMethodError(){
        }
    }
}

