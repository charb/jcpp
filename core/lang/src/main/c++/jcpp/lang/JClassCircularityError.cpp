#include "jcpp/lang/JClassCircularityError.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

        JClassCircularityError::JClassCircularityError():JLinkageError(getClazz()){
        }

        JClassCircularityError::JClassCircularityError(JClass* _class):JLinkageError(_class){
        }

        JClassCircularityError::JClassCircularityError(JString* message):JLinkageError(getClazz()){
            this->detailMessage = message;
        }

        JClassCircularityError::~JClassCircularityError(){
        }
    }
}

