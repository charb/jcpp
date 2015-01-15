#include "jcpp/lang/JError.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JError::JError():JThrowable(getClazz()){
        }

        JError::JError(jcpp::lang::JClass* _class):JThrowable(_class){
        }

        JError::JError(jcpp::lang::JClass* _class, JThrowable* cause):JThrowable(_class){
        	setCause(cause);
        }

        JError::JError(JString* message):JThrowable(getClazz()){
            setMessage(message);
        }

        JError::JError(JString* message, JThrowable *cause):JThrowable(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JError::~JError(){
        }
    }
}

