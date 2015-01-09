#include "org/apache/commons/cli/JMissingArgumentException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JMissingArgumentException::JMissingArgumentException(JString* message):JParseException(getClazz()){
                    this->message=message;
                    option=null;
                }

                JMissingArgumentException::JMissingArgumentException(JOption* option):JParseException(getClazz()){
                    this->option=option;
                }

                JOption* JMissingArgumentException::getOption(){
                    return option;
                }

                JMissingArgumentException::~JMissingArgumentException(){
                }
            }
        }
    }
}
