#include "jcpp/io/JOptionalDataException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{

        JOptionalDataException::JOptionalDataException(jcpp::lang::JClass* _class):JObjectStreamException(_class){
            this->length=new JPrimitiveInt(0);
            this->eof=new JPrimitiveBoolean(false);
        }

        JOptionalDataException::JOptionalDataException():JObjectStreamException(getClazz()){
            this->length=new JPrimitiveInt(0);
            this->eof=new JPrimitiveBoolean(false);
        }

        JOptionalDataException::JOptionalDataException(JString* message) : JObjectStreamException(getClazz()){
            this->detailMessage=message;
            this->length=new JPrimitiveInt(0);
            this->eof=new JPrimitiveBoolean(false);
        }

        JOptionalDataException::JOptionalDataException(jbool end):JObjectStreamException(getClazz()){
            this->length=new JPrimitiveInt(0);
            this->eof=new JPrimitiveBoolean(end);
        }

        jint JOptionalDataException::getLength(){
            return length->get();
        }

        void JOptionalDataException::setLength(jint l){
            length->set(l);
        }

        JPrimitiveInt* JOptionalDataException::getPLength(){
            return length;
        }

        void JOptionalDataException::setPLength(JPrimitiveInt* l){
            this->length=l;
        }

        jbool JOptionalDataException::getEOF(){
            return eof->get();
        }

        void JOptionalDataException::setEOF(jbool eof){
            this->eof->set(eof);
        }

        JPrimitiveBoolean* JOptionalDataException::getPEOF(){
            return eof;
        }

        void JOptionalDataException::setPEOF(JPrimitiveBoolean* eof){
            this->eof=eof;
        }

        JOptionalDataException::~JOptionalDataException(){
        }
    }
}
