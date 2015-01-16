#include "jcpp/xml/parsers/JFactoryConfigurationError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace xml{
        namespace parsers{

            JFactoryConfigurationError::JFactoryConfigurationError(jcpp::lang::JClass* _class):JError(_class){
                this->exception=null;
            }

            JFactoryConfigurationError::JFactoryConfigurationError(JString* message,JException* e):JError(getClazz()){
                this->detailMessage=message;
                this->exception=exception;
            }

            JException* JFactoryConfigurationError::getException(){
                return exception;
            }

            JFactoryConfigurationError::~JFactoryConfigurationError(){
            }
        }
    }
}


