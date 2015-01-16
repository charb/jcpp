#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{

        JConcurrentModificationException::JConcurrentModificationException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JConcurrentModificationException::JConcurrentModificationException():JRuntimeException(getClazz()){
        }

        JConcurrentModificationException::JConcurrentModificationException(JString* message):JRuntimeException(getClazz()){
            this->detailMessage=message;
        }

        JConcurrentModificationException::~JConcurrentModificationException(){
        }
    }
}


