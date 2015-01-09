#include "jcpp/xml/parsers/JParserConfigurationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace xml{
        namespace parsers{

            JParserConfigurationException::JParserConfigurationException(jcpp::lang::JClass* _class):JException(_class){
            }

            JParserConfigurationException::JParserConfigurationException(JString* message):JException(getClazz()){
                this->message=message;
            }

            JParserConfigurationException::~JParserConfigurationException(){
            }
        }
    }
}


