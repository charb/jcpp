#include "org/w3c/dom/JDOMException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace org{
    namespace w3c{
        namespace dom{

            JDOMException::JDOMException(jcpp::lang::JClass* _class):JRuntimeException(_class){
                this->code=new JPrimitiveShort();
            }

            JDOMException::JDOMException(jshort code):JRuntimeException(getClazz()){
                this->code=new JPrimitiveShort(code);
            }

            JDOMException::JDOMException(jshort code,JString* message):JRuntimeException(getClazz()){
                this->code=new JPrimitiveShort(code);
                this->message=message;
            }

            JDOMException::JDOMException(jshort code,JString* message,JThrowable* cause):JRuntimeException(getClazz()){
                this->code=new JPrimitiveShort(code);
                this->message=message;
                this->cause=cause;
            }

            jshort JDOMException::INDEX_SIZE_ERR = 1;
            jshort JDOMException::DOMSTRING_SIZE_ERR = 2;
            jshort JDOMException::HIERARCHY_REQUEST_ERR = 3;
            jshort JDOMException::WRONG_DOCUMENT_ERR = 4;
            jshort JDOMException::INVALID_CHARACTER_ERR = 5;
            jshort JDOMException::NO_DATA_ALLOWED_ERR = 6;
            jshort JDOMException::NO_MODIFICATION_ALLOWED_ERR = 7;
            jshort JDOMException::NOT_FOUND_ERR = 8;
            jshort JDOMException::NOT_SUPPORTED_ERR = 9;
            jshort JDOMException::INUSE_ATTRIBUTE_ERR = 10;
            jshort JDOMException::INVALID_STATE_ERR = 11;
            jshort JDOMException::SYNTAX_ERR = 12;
            jshort JDOMException::INVALID_MODIFICATION_ERR = 13;
            jshort JDOMException::NAMESPACE_ERR = 14;
            jshort JDOMException::INVALID_ACCESS_ERR = 15;
            jshort JDOMException::VALIDATION_ERR = 16;
            jshort JDOMException::TYPE_MISMATCH_ERR = 17;

            JDOMException::~JDOMException(){
            }
        }
    }
}


