#include "jcpp/util/concurrent/JExecutionException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JExecutionException::JExecutionException(jcpp::lang::JClass* _class):JException(_class){
            }

            JExecutionException::JExecutionException():JException(getClazz()){
            }

            JExecutionException::JExecutionException(JString* message):JException(getClazz()){
                this->detailMessage=message;
            }

            JExecutionException::JExecutionException(JString* message,JThrowable* cause):JException(getClazz()){
                this->detailMessage=message;
                this->cause=cause;
            }

            JExecutionException::~JExecutionException(){
            }
        }
    }
}


