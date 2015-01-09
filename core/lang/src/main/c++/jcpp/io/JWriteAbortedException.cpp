#include "jcpp/io/JWriteAbortedException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JWriteAbortedException::JWriteAbortedException(JString* message,JException* ex):JObjectStreamException(getClazz()){
            this->message=message;
            this->detail=ex;
        }

        JWriteAbortedException::JWriteAbortedException():JObjectStreamException(getClazz()){
            this->detail=null;
        }

        JThrowable * JWriteAbortedException::getCause(){
            return getDetail();
        }

        JException* JWriteAbortedException::getDetail(){
            return detail;
        }

        void JWriteAbortedException::setDetail(JException* e){
            this->detail=e;
        }

        JWriteAbortedException::~JWriteAbortedException(){
        }
    }
}
