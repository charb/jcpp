#include "jcpp/lang/reflect/JMember.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassLoader.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            jint JMember::PUBLIC = 0;
            jint JMember::DECLARED = 1;

            JMember::~JMember(){
            }
        }
    }
}
