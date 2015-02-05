#include "jcpp/net/JSocketException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace net{

        JSocketException::JSocketException():JIOException(getClazz()){
        }

        JSocketException::JSocketException(jcpp::lang::JClass* _class):JIOException(_class){
        }


        JSocketException::JSocketException(JString* message) : JIOException(getClazz()){
            this->detailMessage=message;
        }

        JSocketException::~JSocketException(){
        }
    }
}
