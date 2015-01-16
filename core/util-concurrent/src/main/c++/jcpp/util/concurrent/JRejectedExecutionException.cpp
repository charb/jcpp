#include "jcpp/util/concurrent/JRejectedExecutionException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JRejectedExecutionException::JRejectedExecutionException(jcpp::lang::JClass* _class):JRuntimeException(_class){
            }

            JRejectedExecutionException::JRejectedExecutionException():JRuntimeException(getClazz()){
            }

            JRejectedExecutionException::JRejectedExecutionException(JString* message):JRuntimeException(getClazz()){
                this->detailMessage=message;
            }

            JRejectedExecutionException::JRejectedExecutionException(JString* message,JThrowable* cause):JRuntimeException(getClazz()){
                this->detailMessage=message;
                this->cause=cause;
            }

            JRejectedExecutionException::~JRejectedExecutionException(){
            }
        }
    }
}


