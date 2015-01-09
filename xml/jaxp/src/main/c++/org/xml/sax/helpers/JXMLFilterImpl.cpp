#include "org/xml/sax/helpers/JXMLFilterImpl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "org/xml/sax/JSAXParseException.h"
#include "org/xml/sax/JSAXNotRecognizedException.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

                JXMLFilterImpl::JXMLFilterImpl(JClass* _class):JObject(_class){
                    parent=null;
                    locator=null;
                    entityResolver=null;
                    dtdHandler=null;
                    contentHandler=null;
                    errorHandler=null;
                }

                JXMLFilterImpl::JXMLFilterImpl():JObject(getClazz()){
                    parent=null;
                    locator=null;
                    entityResolver=null;
                    dtdHandler=null;
                    contentHandler=null;
                    errorHandler=null;
                }

                JXMLFilterImpl::JXMLFilterImpl(JXMLReader* parent):JObject(getClazz()){
                    parent=null;
                    locator=null;
                    entityResolver=null;
                    dtdHandler=null;
                    contentHandler=null;
                    errorHandler=null;
                    setParent(parent);
                }

                void JXMLFilterImpl::setParent(JXMLReader* parent){
                    this->parent = parent;
                }
                
                JXMLReader* JXMLFilterImpl::getParent(){
                    return parent;
                }

                void JXMLFilterImpl::setFeature(JString* name, jbool value){
                    if (parent != null) {
                        parent->setFeature(name, value);
                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                jbool JXMLFilterImpl::getFeature(JString* name){
                    if (parent != null) {
                        return parent->getFeature(name);
                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                void JXMLFilterImpl::setProperty(JString* name, JObject* value){
                    if (parent != null) {
                        parent->setProperty(name, value);
                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                JObject* JXMLFilterImpl::getProperty(JString* name){
                    if (parent != null) {
                        return parent->getProperty(name);
                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                void JXMLFilterImpl::setEntityResolver(JEntityResolver* resolver){
                    entityResolver = resolver;
                }

                JEntityResolver* JXMLFilterImpl::getEntityResolver(){
                    return entityResolver;
                }

                void JXMLFilterImpl::setDTDHandler(JDTDHandler* handler){
                    dtdHandler = handler;
                }

                JDTDHandler* JXMLFilterImpl::getDTDHandler(){
                    return dtdHandler;
                }

                void JXMLFilterImpl::setContentHandler(JContentHandler* handler){
                    contentHandler = handler;
                }

                JContentHandler* JXMLFilterImpl::getContentHandler(){
                    return contentHandler;
                }

                void JXMLFilterImpl::setErrorHandler(JErrorHandler* handler){
                    errorHandler = handler;
                }

                JErrorHandler* JXMLFilterImpl::getErrorHandler(){
                    return errorHandler;
                }

                void JXMLFilterImpl::parse(JInputSource* input){
                    setupParse();
                    parent->parse(input);
                }

                void JXMLFilterImpl::parse(JString* systemId){
                    parse(new JInputSource(systemId));
                }

                JInputSource* JXMLFilterImpl::resolveEntity(JString* publicId, JString* systemId){
                    if (entityResolver != null) {
                        return entityResolver->resolveEntity(publicId, systemId);
                    } else {
                        return null;
                    }
                }

                void JXMLFilterImpl::notationDecl(JString* name, JString* publicId, JString* systemId){
                    if (dtdHandler != null) {
                        dtdHandler->notationDecl(name, publicId, systemId);
                    }
                }

                void JXMLFilterImpl::unparsedEntityDecl(JString* name, JString* publicId,JString* systemId, JString* notationName){
                    if (dtdHandler != null) {
                        dtdHandler->unparsedEntityDecl(name, publicId, systemId,notationName);
                    }
                }

                void JXMLFilterImpl::setDocumentLocator(JLocator* locator){
                    this->locator = locator;
                    if (contentHandler != null) {
                        contentHandler->setDocumentLocator(locator);
                    }
                }

                void JXMLFilterImpl::startDocument(){
                    if (contentHandler != null) {
                        contentHandler->startDocument();
                    }
                }

                void JXMLFilterImpl::endDocument(){
                    if (contentHandler != null) {
                        contentHandler->endDocument();
                    }
                }

                void JXMLFilterImpl::startPrefixMapping(JString* prefix, JString* uri){
                    if (contentHandler != null) {
                        contentHandler->startPrefixMapping(prefix, uri);
                    }
                }

                void JXMLFilterImpl::endPrefixMapping(JString* prefix){
                    if (contentHandler != null) {
                        contentHandler->endPrefixMapping(prefix);
                    }
                }

                void JXMLFilterImpl::startElement(JString* uri, JString* localName, JString* qName,JAttributes* atts){
                    if (contentHandler != null) {
                        contentHandler->startElement(uri, localName, qName, atts);
                    }
                }

                void JXMLFilterImpl::endElement(JString* uri, JString* localName, JString* qName){
                    if (contentHandler != null) {
                        contentHandler->endElement(uri, localName, qName);
                    }
                }

                void JXMLFilterImpl::characters(JPrimitiveCharArray* ch, jint start, jint length){
                    if (contentHandler != null) {
                        contentHandler->characters(ch, start, length);
                    }
                }

                void JXMLFilterImpl::ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length){
                    if (contentHandler != null) {
                        contentHandler->ignorableWhitespace(ch, start, length);
                    }
                }

                void JXMLFilterImpl::processingInstruction(JString* target, JString* data){
                    if (contentHandler != null) {
                        contentHandler->processingInstruction(target, data);
                    }
                }

                void JXMLFilterImpl::skippedEntity(JString* name){
                    if (contentHandler != null) {
                        contentHandler->skippedEntity(name);
                    }
                }

                void JXMLFilterImpl::warning(JSAXParseException* e){
                    if (errorHandler != null) {
                        errorHandler->warning(e);
                    }
                }

                void JXMLFilterImpl::error(JSAXParseException* e){
                    if (errorHandler != null) {
                        errorHandler->error(e);
                    }
                }

                void JXMLFilterImpl::fatalError(JSAXParseException* e){
                    if (errorHandler != null) {
                        errorHandler->fatalError(e);
                    }
                }

                void JXMLFilterImpl::setupParse(){
                    if (parent == null) {
                        throw new JNullPointerException(new JString("No parent for filter"));
                    }
                    parent->setEntityResolver(this);
                    parent->setDTDHandler(this);
                    parent->setContentHandler(this);
                    parent->setErrorHandler(this);
                }
                
                JXMLFilterImpl::~JXMLFilterImpl(){
                }
            }
        }
    }
}
