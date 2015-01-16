#include "org/apache/commons/cli/JUnrecognizedOptionException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JUnrecognizedOptionException::JUnrecognizedOptionException(JClass* _class):JParseException(_class){
                    this->option=null;
                }

                JUnrecognizedOptionException::JUnrecognizedOptionException():JParseException(getClazz()){
                    this->option=null;
                }

                JUnrecognizedOptionException::JUnrecognizedOptionException(JString* message):JParseException(getClazz()){
                    this->detailMessage=message;
                    this->option=null;
                }

                JUnrecognizedOptionException::JUnrecognizedOptionException(JString* message,JString* option):JParseException(getClazz()){
                    this->detailMessage=message;
                    this->option=option;
                }

                JString* JUnrecognizedOptionException::getOption(){
                    return option;
                }

                JUnrecognizedOptionException::~JUnrecognizedOptionException(){
                }
            }
        }
    }
}

