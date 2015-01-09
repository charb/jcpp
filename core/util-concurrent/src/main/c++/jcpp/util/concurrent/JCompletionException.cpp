#include "jcpp/util/concurrent/JCompletionException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JCompletionException::JCompletionException(jcpp::lang::JClass* _class):JRuntimeException(_class){
            }

            JCompletionException::JCompletionException():JRuntimeException(getClazz()){
            }

            JCompletionException::JCompletionException(JString* message):JRuntimeException(getClazz()){
                this->message=message;
            }

            JCompletionException::JCompletionException(JString* message,JThrowable* cause):JRuntimeException(getClazz()){
                this->message=message;
                this->cause=cause;
            }

            JCompletionException::~JCompletionException(){
            }
        }
    }
}


