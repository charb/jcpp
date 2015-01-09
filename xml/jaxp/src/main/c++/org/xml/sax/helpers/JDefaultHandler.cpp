#include "org/xml/sax/helpers/JDefaultHandler.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

                JDefaultHandler::JDefaultHandler(JClass* _class):JObject(_class){
                }

                JDefaultHandler::JDefaultHandler():JObject(getClazz()){
                }

                JInputSource* JDefaultHandler::resolveEntity(JString* publicId, JString* systemId){
                    return null;
                }

                void JDefaultHandler::notationDecl(JString* name, JString* publicId, JString* systemId){
                }

                void JDefaultHandler::unparsedEntityDecl(JString* name, JString* publicId,JString* systemId, JString* notationName){
                }

                void JDefaultHandler::setDocumentLocator(JLocator* locator){
                }

                void JDefaultHandler::startDocument(){
                }

                void JDefaultHandler::endDocument(){
                }

                void JDefaultHandler::startPrefixMapping(JString* prefix, JString* uri){
                }
                
                void JDefaultHandler::endPrefixMapping(JString* prefix){
                }

                void JDefaultHandler::startElement(JString* uri, JString* localName,JString* qName, JAttributes* attributes){
                }

                void JDefaultHandler::endElement(JString* uri, JString* localName, JString* qName){
                }

                void JDefaultHandler::characters(JPrimitiveCharArray* ch, jint start, jint length){
                }

                void JDefaultHandler::ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length){
                }

                void JDefaultHandler::processingInstruction(JString* target, JString* data){
                }

                void JDefaultHandler::skippedEntity(JString* name){
                }

                void JDefaultHandler::warning(JSAXParseException* e){
                }

                void JDefaultHandler::error(JSAXParseException* e){
                }

                void JDefaultHandler::fatalError(JSAXParseException* e){
                    throw e;
                }
                
                JDefaultHandler::~JDefaultHandler(){
                }
            }
        }
    }
}
