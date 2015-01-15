#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JUnsupportedOperationException::JUnsupportedOperationException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JUnsupportedOperationException::JUnsupportedOperationException():JRuntimeException(getClazz()){
        }

        JUnsupportedOperationException::JUnsupportedOperationException(JString* message):JRuntimeException(getClazz()){
            this->message=message;
        }

        JUnsupportedOperationException::~JUnsupportedOperationException(){
        }
    }
}



