#include "jcpp/io/JSerialCallbackContext.h"
#include "jcpp/io/JObjectStreamClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace io{

        JSerialCallbackContext::JSerialCallbackContext(JObject* obj,JObjectStreamClass* desc) {
            curObj = obj;
            curDesc = desc;
        }

        JObject* JSerialCallbackContext::getObj(){
            return curObj;
        }

        JObjectStreamClass* JSerialCallbackContext::getDesc(){
            return curDesc;
        }
    }
}

