#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JInternalError::JInternalError():JVirtualMachineError(getClazz()){
        }

        JInternalError::JInternalError(jcpp::lang::JClass* _class):JVirtualMachineError(_class){
        }

        JInternalError::JInternalError(JString* message):JVirtualMachineError(getClazz()){
            setMessage(message);
        }

        JInternalError::JInternalError(JString* message, JThrowable *cause):JVirtualMachineError(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JInternalError::~JInternalError(){
        }
    }
}

