#include "org/xml/sax/JSAXNotSupportedException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace org{
    namespace xml{
        namespace sax{

            JSAXNotSupportedException::JSAXNotSupportedException(jcpp::lang::JClass* _class):JSAXException(_class){
            }

            JSAXNotSupportedException::JSAXNotSupportedException():JSAXException(getClazz()){
            }

            JSAXNotSupportedException::JSAXNotSupportedException(JString* message):JSAXException(getClazz()){
                this->message=message;
            }

            JSAXNotSupportedException::~JSAXNotSupportedException(){
            }
        }
    }
}


