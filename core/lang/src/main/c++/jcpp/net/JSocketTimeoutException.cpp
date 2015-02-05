#include "jcpp/net/JSocketTimeoutException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace net{

        JSocketTimeoutException::JSocketTimeoutException():JInterruptedIOException(getClazz()){
        }

        JSocketTimeoutException::JSocketTimeoutException(jcpp::lang::JClass* _class):JInterruptedIOException(_class){
        }

        JSocketTimeoutException::JSocketTimeoutException(JString* message) : JInterruptedIOException(getClazz()){
            this->detailMessage=message;
        }

        JSocketTimeoutException::~JSocketTimeoutException(){
        }
    }
}
