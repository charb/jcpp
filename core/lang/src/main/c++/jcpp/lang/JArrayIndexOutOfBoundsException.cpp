#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JArrayIndexOutOfBoundsException::JArrayIndexOutOfBoundsException():JIndexOutOfBoundsException(getClazz()){
        }

        JArrayIndexOutOfBoundsException::JArrayIndexOutOfBoundsException(JString* message):JIndexOutOfBoundsException(getClazz()){
            setMessage(message);
        }

        JArrayIndexOutOfBoundsException::~JArrayIndexOutOfBoundsException(){
        }
    }
}
