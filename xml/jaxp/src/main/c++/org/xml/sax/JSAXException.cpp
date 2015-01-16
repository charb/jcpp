#include "org/xml/sax/JSAXException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace org{
    namespace xml{
        namespace sax{

            JSAXException::JSAXException(jcpp::lang::JClass* _class):JException(_class){
                this->exception=null;
            }

            JSAXException::JSAXException():JException(getClazz()){
                this->exception=null;
            }

            JSAXException::JSAXException(JString* message):JException(getClazz()){
                this->exception=null;
                this->detailMessage=message;
            }

            JSAXException::JSAXException(JException* exception):JException(getClazz()){
                this->exception=exception;
                this->cause=exception;
            }

            JSAXException::JSAXException(JString* message,JException* cause):JException(getClazz()){
                this->exception=exception;
                this->detailMessage=message;
                this->cause=exception;
            }

            JString* JSAXException::getMessage(){
                JString* message = JException::getMessage();
                if (message == null && exception != null) {
                    return exception->getMessage();
                } else {
                    return message;
                }
            }

            JException* JSAXException::getException(){
                return exception;
            }

            JThrowable* JSAXException::getCause() {
                return exception;
            }

            JSAXException::~JSAXException(){
            }
        }
    }
}


