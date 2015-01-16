#include "jcpp/lang/JNoSuchMethodError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNoSuchMethodError::JNoSuchMethodError():JIncompatibleClassChangeError(getClazz()){
        }

        JNoSuchMethodError::JNoSuchMethodError(jcpp::lang::JClass* _class):JIncompatibleClassChangeError(_class){
        }

        JNoSuchMethodError::JNoSuchMethodError(JString* message):JIncompatibleClassChangeError(getClazz()){
            this->detailMessage = message;
        }

        JNoSuchMethodError::JNoSuchMethodError(JString* message, JThrowable *cause):JIncompatibleClassChangeError(getClazz()){
            this->detailMessage = message;
            this->cause = cause;
        }

        JNoSuchMethodError::~JNoSuchMethodError(){
        }
    }
}

