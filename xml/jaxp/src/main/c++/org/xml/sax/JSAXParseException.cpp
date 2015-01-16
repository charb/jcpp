#include "org/xml/sax/JSAXParseException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang::reflect;

namespace org{
    namespace xml{
        namespace sax{

            JSAXParseException::JSAXParseException(jcpp::lang::JClass* _class):JSAXException(_class){
                this->publicId=null;
                this->systemId=null;
                lineNumber=new JPrimitiveInt(-1);
                columnNumber=new JPrimitiveInt(-1);
            }

            JSAXParseException::JSAXParseException():JSAXException(getClazz()){
                this->publicId=null;
                this->systemId=null;
                lineNumber=new JPrimitiveInt(-1);
                columnNumber=new JPrimitiveInt(-1);
            }

            JSAXParseException::JSAXParseException(JString* message):JSAXException(getClazz()){
                this->detailMessage=message;
                this->publicId=null;
                this->systemId=null;
                lineNumber=new JPrimitiveInt(-1);
                columnNumber=new JPrimitiveInt(-1);
            }

            JSAXParseException::JSAXParseException(JString* message,JException* exception):JSAXException(getClazz()){
                this->detailMessage=message;
                this->exception=exception;
                this->cause=exception;
                this->publicId=null;
                this->systemId=null;
                lineNumber=new JPrimitiveInt(-1);
                columnNumber=new JPrimitiveInt(-1);
            }

            JSAXParseException::JSAXParseException(JString* message, JString* publicId, JString* systemId,jint lineNumber, jint columnNumber):JSAXException(getClazz()){
                this->detailMessage=message;
                this->publicId=publicId;
                this->systemId=systemId;
                this->lineNumber=new JPrimitiveInt(lineNumber);
                this->columnNumber=new JPrimitiveInt(columnNumber);
            }

            JSAXParseException::JSAXParseException(JString* message, JString* publicId, JString* systemId,jint lineNumber, jint columnNumber, JException* exception):JSAXException(getClazz()){
                this->detailMessage=message;
                this->exception=exception;
                this->cause=exception;
                this->publicId=publicId;
                this->systemId=systemId;
                this->lineNumber=new JPrimitiveInt(lineNumber);
                this->columnNumber=new JPrimitiveInt(columnNumber);
            }

            JString* JSAXParseException::getPublicId(){
                return publicId;
            }

            JString* JSAXParseException::getSystemId(){
                return systemId;
            }

            jint JSAXParseException::getLineNumber(){
                return lineNumber->get();
            }

            jint JSAXParseException::getColumnNumber(){
                return columnNumber->get();
            }

            JString* JSAXParseException::toString(){
                JStringBuilder* buf = new JStringBuilder(getClass()->getName());
                JString* message = getMessage();
                if (publicId!=null){
                    buf->append(new JString("publicId: "))
                       ->append(publicId);
                }

                if (systemId!=null){
                    buf->append(new JString("; systemId: "))
                       ->append(systemId);
                }
                if (lineNumber->get()!=-1){
                    buf->append(new JString("; lineNumber: "))
                       ->append(lineNumber->get());
                }
                if (columnNumber->get()!=-1){  
                    buf->append(new JString("; columnNumber: "))
                       ->append(columnNumber->get());
                }

                if (message!=null){
                    buf->append(new JString("; "))
                       ->append(message);
                }
                return buf->toString();
            }

            JSAXParseException::~JSAXParseException(){
            }
        }
    }
}


