#include "jcpp/lang/JEnumConstantNotPresentException.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JEnumConstantNotPresentException::JEnumConstantNotPresentException():JRuntimeException(getClazz()){
            this->enumType=null;
            this->constantName=null;
        }

        JEnumConstantNotPresentException::JEnumConstantNotPresentException(jcpp::lang::JClass* enumType, JString* constantName):JRuntimeException(getClazz()){
            this->enumType=enumType;
            this->constantName=constantName;
        }

        jcpp::lang::JClass* JEnumConstantNotPresentException::getEnumType(){
            return enumType;
        }

        JString* JEnumConstantNotPresentException::getConstantName(){
            return constantName;
        }

        JEnumConstantNotPresentException::~JEnumConstantNotPresentException(){
        }
    }
}

