#include "jcpp/lang/JOutOfMemoryError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JOutOfMemoryError::JOutOfMemoryError():JVirtualMachineError(getClazz()){
        }

        JOutOfMemoryError::JOutOfMemoryError(jcpp::lang::JClass* _class):JVirtualMachineError(_class){
        }

        JOutOfMemoryError::JOutOfMemoryError(JString* message):JVirtualMachineError(getClazz()){
            this->detailMessage = message;
        }

        JOutOfMemoryError::JOutOfMemoryError(JString* message, JThrowable *cause):JVirtualMachineError(getClazz()){
            this->detailMessage = message;
            this->cause = cause;
        }

        JOutOfMemoryError::~JOutOfMemoryError(){
        }
    }
}

