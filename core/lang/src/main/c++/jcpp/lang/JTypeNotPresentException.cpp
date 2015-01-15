#include "jcpp/lang/JTypeNotPresentException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JTypeNotPresentException::JTypeNotPresentException():JRuntimeException(getClazz()){
        }

        JTypeNotPresentException::JTypeNotPresentException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JTypeNotPresentException::JTypeNotPresentException(JString* typeName,JString* message):JRuntimeException(getClazz()){
            this->typeName=typeName;
            setMessage(message);
        }

        JString* JTypeNotPresentException::getTypeName(){
            return typeName;
        }

        JTypeNotPresentException::~JTypeNotPresentException(){
        }
    }
}

