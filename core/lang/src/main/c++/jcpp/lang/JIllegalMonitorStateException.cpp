#include "jcpp/lang/JIllegalMonitorStateException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIllegalMonitorStateException::JIllegalMonitorStateException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JIllegalMonitorStateException::JIllegalMonitorStateException():JRuntimeException(getClazz()){
        }

        JIllegalMonitorStateException::JIllegalMonitorStateException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JIllegalMonitorStateException::~JIllegalMonitorStateException(){
        }
    }
}


