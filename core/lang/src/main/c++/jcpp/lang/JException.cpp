#include "jcpp/lang/JException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JException::JException():JThrowable(getClazz()){
        }

        JException::JException(jcpp::lang::JClass* _class):JThrowable(_class){
        }

        JException::JException(JString* message):JThrowable(getClazz()){
            setMessage(message);
        }

        JException::JException(JString* message, JThrowable *cause):JThrowable(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JException::~JException(){
        }
    }
}
