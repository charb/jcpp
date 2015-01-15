#include "jcpp/lang/JVirtualMachineError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JVirtualMachineError::JVirtualMachineError():JError(getClazz()){
        }

        JVirtualMachineError::JVirtualMachineError(jcpp::lang::JClass* _class):JError(_class){
        }

        JVirtualMachineError::JVirtualMachineError(JString* message):JError(getClazz()){
            this->message = message;
        }

        JVirtualMachineError::JVirtualMachineError(JString* message, JThrowable *cause):JError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JVirtualMachineError::~JVirtualMachineError(){
        }
    }
}

