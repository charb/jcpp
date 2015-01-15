#include "jcpp/lang/reflect/JUndeclaredThrowableException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{

            JUndeclaredThrowableException::JUndeclaredThrowableException():JRuntimeException(getClazz()){
                undeclaredThrowable=null;
            }

            JUndeclaredThrowableException::JUndeclaredThrowableException(JThrowable* undeclaredThrowable):JRuntimeException(getClazz()){
                this->undeclaredThrowable=undeclaredThrowable;
            }

            JUndeclaredThrowableException::JUndeclaredThrowableException(JThrowable* undeclaredThrowable,JString* message):JRuntimeException(getClazz()){
                this->undeclaredThrowable=undeclaredThrowable;
                setMessage(message);
            }

            JThrowable* JUndeclaredThrowableException::getUndeclaredThrowable(){
                return undeclaredThrowable;
            }

            JUndeclaredThrowableException::~JUndeclaredThrowableException(){
            }
        }
    }
}
