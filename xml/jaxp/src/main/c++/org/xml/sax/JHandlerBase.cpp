#include "org/xml/sax/JHandlerBase.h"
#include "jcpp/lang/JClass.h"

namespace org{
    namespace xml{
        namespace sax{

            JHandlerBase::JHandlerBase(JClass* _class):JObject(_class){
            }

            JHandlerBase::JHandlerBase():JObject(getClazz()){
            }

            JInputSource* JHandlerBase::resolveEntity(JString* publicId, JString* systemId){
                return null;
            }

            void JHandlerBase::notationDecl(JString* name, JString* publicId, JString* systemId){
            }

            void JHandlerBase::unparsedEntityDecl(JString* name, JString* publicId,JString* systemId, JString* notationName){
            }

            void JHandlerBase::setDocumentLocator(JLocator* locator){
            }

            void JHandlerBase::startDocument(){
            }

            void JHandlerBase::endDocument(){
            }

            void JHandlerBase::startElement(JString* name, JAttributeList* attributes){
            }

            void JHandlerBase::endElement(JString* name){
            }

            void JHandlerBase::characters(JPrimitiveCharArray* ch, jint start, jint length){
            }

            void JHandlerBase::ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length){
            }

            void JHandlerBase::processingInstruction(JString* target, JString* data){
            }

            void JHandlerBase::warning(JSAXParseException* e){
            }

            void JHandlerBase::error(JSAXParseException* e){
            }

            void JHandlerBase::fatalError(JSAXParseException* e){
                throw e;
            }

            JHandlerBase::~JHandlerBase(){
            }
        }
    }
}
