#include "jcpp/util/concurrent/JBrokenBarrierException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{

            JBrokenBarrierException::JBrokenBarrierException(jcpp::lang::JClass* _class):JException(_class){
            }

            JBrokenBarrierException::JBrokenBarrierException():JException(getClazz()){
            }

            JBrokenBarrierException::JBrokenBarrierException(JString* message):JException(getClazz()){
                this->message=message;
            }

            JBrokenBarrierException::JBrokenBarrierException(JString* message,JThrowable* cause):JException(getClazz()){
                this->message=message;
                this->cause=cause;
            }

            JBrokenBarrierException::~JBrokenBarrierException(){
            }
        }
    }
}


