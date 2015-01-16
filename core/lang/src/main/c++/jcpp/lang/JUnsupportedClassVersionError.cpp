#include "jcpp/lang/JUnsupportedClassVersionError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JUnsupportedClassVersionError::JUnsupportedClassVersionError():jcpp::lang::JClassFormatError(getClazz()){
        }

        JUnsupportedClassVersionError::JUnsupportedClassVersionError(jcpp::lang::JClass* _class):jcpp::lang::JClassFormatError(_class){
        }

        JUnsupportedClassVersionError::JUnsupportedClassVersionError(JString* message):jcpp::lang::JClassFormatError(getClazz()){
            this->detailMessage = message;
        }

        JUnsupportedClassVersionError::~JUnsupportedClassVersionError(){
        }
    }
}

