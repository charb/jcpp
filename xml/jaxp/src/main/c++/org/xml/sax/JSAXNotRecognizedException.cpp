#include "org/xml/sax/JSAXNotRecognizedException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace org{
    namespace xml{
        namespace sax{

            JSAXNotRecognizedException::JSAXNotRecognizedException(jcpp::lang::JClass* _class):JSAXException(_class){
            }

            JSAXNotRecognizedException::JSAXNotRecognizedException():JSAXException(getClazz()){
            }

            JSAXNotRecognizedException::JSAXNotRecognizedException(JString* message):JSAXException(getClazz()){
                this->message=message;
            }

            JSAXNotRecognizedException::~JSAXNotRecognizedException(){
            }
        }
    }
}


