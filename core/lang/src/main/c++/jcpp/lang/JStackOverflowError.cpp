#include "jcpp/lang/JStackOverflowError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JStackOverflowError::JStackOverflowError():JVirtualMachineError(getClazz()){
        }

        JStackOverflowError::JStackOverflowError(jcpp::lang::JClass* _class):JVirtualMachineError(_class){
        }

        JStackOverflowError::JStackOverflowError(JString* message):JVirtualMachineError(getClazz()){
            this->detailMessage = message;
        }

        JStackOverflowError::~JStackOverflowError(){
        }
    }
}

