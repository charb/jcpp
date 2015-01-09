#include "jcpp/io/JIOError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JIOError::JIOError():JError(getClazz()){
        }

        JIOError::JIOError(JString* message):JError(getClazz()){
            this->message=message;
        }

        JIOError::JIOError(JThrowable* cause):JError(getClazz()){
            this->cause=cause;
        }

        JIOError::~JIOError(){
        }
    }
}
