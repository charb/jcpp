#include "jcpp/lang/JVerifyError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JVerifyError::JVerifyError():JLinkageError(getClazz()){
        }

        JVerifyError::JVerifyError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JVerifyError::JVerifyError(JString* message):JLinkageError(getClazz()){
            this->detailMessage = message;
        }

        JVerifyError::~JVerifyError(){
        }
    }
}

