#include "jcpp/lang/JUnknownError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JUnknownError::JUnknownError():JVirtualMachineError(getClazz()){
        }

        JUnknownError::JUnknownError(jcpp::lang::JClass* _class):JVirtualMachineError(_class){
        }

        JUnknownError::JUnknownError(JString* message):JVirtualMachineError(getClazz()){
            this->detailMessage = message;
        }

        JUnknownError::~JUnknownError(){
        }
    }
}

