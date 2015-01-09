#include "org/apache/commons/cli/JAlreadySelectedException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JAlreadySelectedException::JAlreadySelectedException(JString* message):JParseException(getClazz()){
                    this->message=message;
                    group=null;
                    option=null;
                }

                JAlreadySelectedException::JAlreadySelectedException(JOptionGroup* group,JOption* option):JParseException(getClazz()){
                    this->group=group;
                    this->option=option;
                }

                JOptionGroup* JAlreadySelectedException::getOptionGroup(){
                    return group;
                }

                JOption* JAlreadySelectedException::getOption(){
                    return option;
                }

                JAlreadySelectedException::~JAlreadySelectedException(){
                }
            }
        }
    }
}

