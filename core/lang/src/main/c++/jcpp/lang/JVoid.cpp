#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveVoid.h"

namespace jcpp{
    namespace lang{

        jcpp::lang::JClass* JVoid::TYPE = JPrimitiveVoid::getClazz();

        JVoid::~JVoid(){
        }
    }
}

