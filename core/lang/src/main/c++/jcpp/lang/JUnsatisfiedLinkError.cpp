#include "jcpp/lang/JUnsatisfiedLinkError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JUnsatisfiedLinkError::JUnsatisfiedLinkError():JLinkageError(getClazz()){
        }

        JUnsatisfiedLinkError::JUnsatisfiedLinkError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JUnsatisfiedLinkError::JUnsatisfiedLinkError(JString* message):JLinkageError(getClazz()){
            this->message = message;
        }

        JUnsatisfiedLinkError::~JUnsatisfiedLinkError(){
        }
    }
}

