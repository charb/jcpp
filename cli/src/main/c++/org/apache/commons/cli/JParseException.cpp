#include "org/apache/commons/cli/JParseException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JParseException::JParseException(JClass* _class):JException(_class){
                }

                JParseException::JParseException():JException(getClazz()){
                }

                JParseException::JParseException(JString* message):JException(getClazz()){
                    this->message=message;
                }

                JParseException::~JParseException(){
                }
            }
        }
    }
}

