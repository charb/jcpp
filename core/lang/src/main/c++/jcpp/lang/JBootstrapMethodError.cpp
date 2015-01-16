#include "jcpp/lang/JBootstrapMethodError.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JBootstrapMethodError::JBootstrapMethodError():JLinkageError(getClazz()){
        }

        JBootstrapMethodError::JBootstrapMethodError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JBootstrapMethodError::JBootstrapMethodError(JString* message):JLinkageError(getClazz()){
            this->detailMessage = message;
        }

        JBootstrapMethodError::~JBootstrapMethodError(){
        }
    }
}

