#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JIndexOutOfBoundsException::JIndexOutOfBoundsException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JIndexOutOfBoundsException::JIndexOutOfBoundsException():JRuntimeException(getClazz()){
        }

        JIndexOutOfBoundsException::JIndexOutOfBoundsException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JIndexOutOfBoundsException::~JIndexOutOfBoundsException(){
        }
    }
}
