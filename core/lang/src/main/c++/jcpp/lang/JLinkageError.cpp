#include "jcpp/lang/JLinkageError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JLinkageError::JLinkageError():JError(getClazz()){
        }

        JLinkageError::JLinkageError(jcpp::lang::JClass* _class):JError(_class){
        }

        JLinkageError::JLinkageError(JString* message):JError(getClazz()){
            this->detailMessage = message;
        }

        JLinkageError::JLinkageError(JString* message, JThrowable *cause):JError(getClazz()){
            this->detailMessage = message;
            this->cause = cause;
        }

        JLinkageError::~JLinkageError(){
        }
    }
}

