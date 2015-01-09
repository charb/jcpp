#include "org/w3c/dom/JTypeInfo.h"
#include "jcpp/lang/JClass.h"

namespace org{
    namespace w3c{
        namespace dom{

            jint JTypeInfo::DERIVATION_RESTRICTION = 0x00000001 ;
                
            jint JTypeInfo::DERIVATION_EXTENSION = 0x00000002;
            
            jint JTypeInfo::DERIVATION_UNION = 0x00000004;

            jint JTypeInfo::DERIVATION_LIST = 0x00000008;

            JTypeInfo::~JTypeInfo(){
            }
        }
    }
}
