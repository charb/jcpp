#include "jcpp/util/concurrent/JCancellationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{
            JCancellationException::JCancellationException(jcpp::lang::JClass* _class):JIllegalStateException(_class){
            }

            JCancellationException::JCancellationException():JIllegalStateException(getClazz()){
            }

            JCancellationException::JCancellationException(JString* message):JIllegalStateException(getClazz()){
                this->detailMessage=message;
            }

            JCancellationException::JCancellationException(JString* message,JThrowable* cause):JIllegalStateException(getClazz()){
                this->detailMessage=message;
                this->cause=cause;
            }

            JCancellationException::~JCancellationException(){
            }
        }
    }
}


