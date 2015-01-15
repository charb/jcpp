#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JNullPointerException::JNullPointerException():JRuntimeException(getClazz()){
        }

        JNullPointerException::JNullPointerException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JNullPointerException::~JNullPointerException(){
        }
    }
}
