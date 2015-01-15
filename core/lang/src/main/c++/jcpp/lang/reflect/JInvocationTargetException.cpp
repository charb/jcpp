#include "jcpp/lang/reflect/JInvocationTargetException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        namespace reflect{

            JInvocationTargetException::JInvocationTargetException():JReflectiveOperationException(getClazz()){
                target=null;
            }

            JInvocationTargetException::JInvocationTargetException(JThrowable* target):JReflectiveOperationException(getClazz()){
                this->target=target;
            }

            JInvocationTargetException::JInvocationTargetException(JThrowable* target,JString* message):JReflectiveOperationException(getClazz()){
                this->target=target;
                setMessage(message);
            }

            JThrowable* JInvocationTargetException::getTargetException(){
                return target;
            }

            JInvocationTargetException::~JInvocationTargetException(){
            }
        }
    }
}
