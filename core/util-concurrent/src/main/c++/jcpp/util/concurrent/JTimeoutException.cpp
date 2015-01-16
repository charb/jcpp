#include "jcpp/util/concurrent/JTimeoutException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JTimeoutException::JTimeoutException(jcpp::lang::JClass* _class):JException(_class){
            }

            JTimeoutException::JTimeoutException():JException(getClazz()){
            }

            JTimeoutException::JTimeoutException(JString* message):JException(getClazz()){
                this->detailMessage=message;
            }

            JTimeoutException::JTimeoutException(JString* message,JThrowable* cause):JException(getClazz()){
                this->detailMessage=message;
                this->cause=cause;
            }

            JTimeoutException::~JTimeoutException(){
            }
        }
    }
}


