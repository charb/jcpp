#include "jcpp/lang/annotation/JAnnotation.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        namespace annotation{

            jcpp::lang::JClass* JAnnotation::annotationType(){
                JObject* obj=dynamic_cast<JObject*>(this);
                return obj->getClass();
            }

            JAnnotation::~JAnnotation(){
            }
        }
    }
}

