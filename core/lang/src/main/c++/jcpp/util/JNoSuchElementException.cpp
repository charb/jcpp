#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        JNoSuchElementException::JNoSuchElementException():JRuntimeException(getClazz()){
        }

        JNoSuchElementException::JNoSuchElementException(JString* message):JRuntimeException(getClazz()){
            this->detailMessage=message;
        }

        JNoSuchElementException::~JNoSuchElementException(){
        }
    }
}

