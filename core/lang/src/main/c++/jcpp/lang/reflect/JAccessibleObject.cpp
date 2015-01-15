#include "jcpp/lang/reflect/JAccessibleObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassLoader.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            JAccessibleObject::JAccessibleObject(jcpp::lang::JClass* clazz):JObject(clazz){
            }

            JAccessibleObject::~JAccessibleObject(){
            }
        }
    }
}

