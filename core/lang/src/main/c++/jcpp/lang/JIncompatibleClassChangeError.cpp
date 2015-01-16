#include "jcpp/lang/JIncompatibleClassChangeError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIncompatibleClassChangeError::JIncompatibleClassChangeError():JLinkageError(getClazz()){
        }

        JIncompatibleClassChangeError::JIncompatibleClassChangeError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JIncompatibleClassChangeError::JIncompatibleClassChangeError(JString* message):JLinkageError(getClazz()){
            this->detailMessage = message;
        }

        JIncompatibleClassChangeError::JIncompatibleClassChangeError(JString* message, JThrowable *cause):JLinkageError(getClazz()){
            this->detailMessage = message;
            this->cause = cause;
        }

        JIncompatibleClassChangeError::~JIncompatibleClassChangeError(){
        }
    }
}

