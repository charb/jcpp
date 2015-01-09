#include "org/xml/sax/helpers/JXMLReaderAdapter.h"
#include "org/xml/sax/helpers/JXMLReaderFactory.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JVector.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "org/xml/sax/JSAXParseException.h"
#include "org/xml/sax/JSAXNotRecognizedException.h"
#include "org/xml/sax/JSAXNotSupportedException.h"

using namespace jcpp::util;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

                JXMLReaderAdapter::JXMLReaderAdapter(JClass* _class):JObject(_class){
                    xmlReader=null;
                    documentHandler=null;
                    qAtts=null;
                }

                JXMLReaderAdapter::JXMLReaderAdapter():JObject(getClazz()){
                    xmlReader=null;
                    documentHandler=null;
                    qAtts=null;
                    setup(JXMLReaderFactory::createXMLReader());
                }

                JXMLReaderAdapter::JXMLReaderAdapter(JXMLReader* xmlReader):JObject(getClazz()){
                    xmlReader=null;
                    documentHandler=null;
                    qAtts=null;
                    setup(xmlReader);
                }

                JXMLReaderAdapter::JAttributesAdapter::JAttributesAdapter(JClass* _class,JXMLReaderAdapter* adapter):JObject(_class){
                    this->adapter=adapter;
                    attributes=null;
                }

                JXMLReaderAdapter::JAttributesAdapter::JAttributesAdapter(JXMLReaderAdapter* adapter):JObject(getClazz()){
                    this->adapter=adapter;
                    attributes=null;
                }

                void JXMLReaderAdapter::JAttributesAdapter::setAttributes(JAttributes* attributes){
                    this->attributes=attributes;
                }

                jint JXMLReaderAdapter::JAttributesAdapter::getLength(){
                    return attributes->getLength();
                }

                JString* JXMLReaderAdapter::JAttributesAdapter::getName(jint i){
                    return attributes->getQName(i);
                }

                JString* JXMLReaderAdapter::JAttributesAdapter::getType(jint i){
                    return attributes->getType(i);
                }

                JString* JXMLReaderAdapter::JAttributesAdapter::getValue(jint i){
                    return attributes->getValue(i);
                }

                JString* JXMLReaderAdapter::JAttributesAdapter::getType(JString* qName){
                    return attributes->getType(qName);
                }

                JString* JXMLReaderAdapter::JAttributesAdapter::getValue(JString* qName){
                    return attributes->getValue(qName);
                }

                JXMLReaderAdapter::JAttributesAdapter::~JAttributesAdapter(){
                }
                
                void JXMLReaderAdapter::setup(JXMLReader* xmlReader){
                    if (xmlReader == null) {
                        throw new JNullPointerException(new JString("XMLReader must not be null"));
                    }
                    this->xmlReader = xmlReader;
                    qAtts = new JAttributesAdapter(this);
                }

                void JXMLReaderAdapter::setEntityResolver(JEntityResolver* resolver){
                    xmlReader->setEntityResolver(resolver);
                }

                void JXMLReaderAdapter::setDTDHandler(JDTDHandler* handler){
                    xmlReader->setDTDHandler(handler);
                }

                void JXMLReaderAdapter::setDocumentHandler(JDocumentHandler* handler){
                    documentHandler = handler;
                }

                void JXMLReaderAdapter::setErrorHandler(JErrorHandler* handler){
                    xmlReader->setErrorHandler(handler);
                }

                void JXMLReaderAdapter::parse(JString* systemId){
                    parse(new JInputSource(systemId));
                }

                void JXMLReaderAdapter::parse(JInputSource* input){
                    setupXMLReader();
                    xmlReader->parse(input);
                }

                void JXMLReaderAdapter::setupXMLReader(){
                    xmlReader->setFeature(new JString("http://xml.org/sax/features/namespace-prefixes"), true);
                    try {
                        xmlReader->setFeature(new JString("http://xml.org/sax/features/namespaces"),false);
                    } catch (JSAXException* e) {
                    }
                    xmlReader->setContentHandler(this);
                }

                void JXMLReaderAdapter::setDocumentLocator(JLocator* locator){
                    if (documentHandler != null){
                        documentHandler->setDocumentLocator(locator);
                    }
                }

                void JXMLReaderAdapter::startDocument(){
                    if (documentHandler != null){
                        documentHandler->startDocument();
                    }
                }

                void JXMLReaderAdapter::endDocument(){
                    if (documentHandler != null){
                        documentHandler->endDocument();
                    }
                }

                void JXMLReaderAdapter::startPrefixMapping(JString* prefix, JString* uri){
                }

                void JXMLReaderAdapter::endPrefixMapping(JString* prefix){
                }

                void JXMLReaderAdapter::startElement(JString* uri, JString* localName,JString* qName, JAttributes* atts){
                    if (documentHandler != null) {
                        qAtts->setAttributes(atts);
                        documentHandler->startElement(qName, qAtts);
                    }
                }

                void JXMLReaderAdapter::endElement(JString* uri, JString* localName,JString* qName){
                    if (documentHandler != null){
                        documentHandler->endElement(qName);
                    }
                }

                void JXMLReaderAdapter::characters(JPrimitiveCharArray* ch, jint start, jint length){
                    if (documentHandler != null){
                        documentHandler->characters(ch, start, length);
                    }
                }

                void JXMLReaderAdapter::ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length){
                    if (documentHandler != null){
                        documentHandler->ignorableWhitespace(ch, start, length);
                    }
                }

                void JXMLReaderAdapter::processingInstruction(JString* target, JString* data){
                    if (documentHandler != null){
                        documentHandler->processingInstruction(target, data);
                    }
                }

                void JXMLReaderAdapter::skippedEntity(JString* name){
                }
                
                JXMLReaderAdapter::~JXMLReaderAdapter(){
                }
            }
        }
    }
}
