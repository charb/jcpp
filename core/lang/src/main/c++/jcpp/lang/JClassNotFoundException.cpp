#include "jcpp/lang/JClassNotFoundException.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JClassNotFoundException::JClassNotFoundException():JReflectiveOperationException(getClazz()){
            ex=null;
        }

        JClassNotFoundException::JClassNotFoundException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
            ex=null;
        }

        void JClassNotFoundException::setCause(JThrowable* th){
            this->cause=th;
            this->ex=th;
        }

        JThrowable* JClassNotFoundException::getException(){
            return ex;
        }

        JThrowable* JClassNotFoundException::getCause(){
            return ex;
        }

        JClassNotFoundException::~JClassNotFoundException(){
        }
    }
}
