#include "jcpp/lang/JClassFormatError.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JClassFormatError::JClassFormatError():JLinkageError(getClazz()){
        }

        JClassFormatError::JClassFormatError(JClass* _class):JLinkageError(_class){
        }

        JClassFormatError::JClassFormatError(JString* message):JLinkageError(getClazz()){
            this->detailMessage = message;
        }

        JClassFormatError::~JClassFormatError(){
        }
    }
}

