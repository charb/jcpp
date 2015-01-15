#include "jcpp/lang/JStringIndexOutOfBoundsException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JStringIndexOutOfBoundsException::JStringIndexOutOfBoundsException(jcpp::lang::JClass* _class):JIndexOutOfBoundsException(_class){
        }

        JStringIndexOutOfBoundsException::JStringIndexOutOfBoundsException():JIndexOutOfBoundsException(getClazz()){
        }

        JStringIndexOutOfBoundsException::JStringIndexOutOfBoundsException(JString* message):JIndexOutOfBoundsException(getClazz()){
            setMessage(message);
        }

        JStringIndexOutOfBoundsException::~JStringIndexOutOfBoundsException(){
        }
    }
}
