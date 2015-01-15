#include "jcpp/lang/JNoClassDefFoundError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNoClassDefFoundError::JNoClassDefFoundError():JLinkageError(getClazz()){
        }

        JNoClassDefFoundError::JNoClassDefFoundError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JNoClassDefFoundError::JNoClassDefFoundError(JString* message):JLinkageError(getClazz()){
            this->message = message;
        }

        JNoClassDefFoundError::JNoClassDefFoundError(JString* message, JThrowable *cause):JLinkageError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JNoClassDefFoundError::~JNoClassDefFoundError(){
        }
    }
}

