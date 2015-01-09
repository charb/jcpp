#include "jcpp/rmi/server/connection/JConnectionException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JConnectionException::JConnectionException():JException(getClazz()){
                }

                JConnectionException::JConnectionException(JClass* _class):JException(_class){
                }

                JConnectionException::JConnectionException(JString* message):JException(getClazz()){
                    this->message=message;
                }

                JConnectionException::JConnectionException(JString* message,JThrowable* cause):JException(getClazz()){
                    this->message=message;
                    this->cause=cause;
                }

                JConnectionException::~JConnectionException(){
                }
            }
        }
    }
}
