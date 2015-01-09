#include "junit/framework/JAssertionFailedError.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JAssertionError.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace junit{
    namespace framework{
        
        JAssertionFailedError::JAssertionFailedError(JClass* _class):JAssertionError(_class){
        }

        JAssertionFailedError::JAssertionFailedError():JAssertionError(getClazz()){
        }

        JAssertionFailedError::JAssertionFailedError(JString* message):JAssertionError(getClazz()){
            this->message=message;
        }

        JAssertionFailedError::~JAssertionFailedError(){
        }
    }
}

