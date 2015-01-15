#include "jcpp/lang/JArrayStoreException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JArrayStoreException::JArrayStoreException():JRuntimeException(getClazz()){
        }

        JArrayStoreException::JArrayStoreException(JString* message):JRuntimeException(getClazz()){
            setMessage(message);
        }

        JArrayStoreException::~JArrayStoreException(){
        }
    }
}
