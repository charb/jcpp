#include "org/xml/sax/helpers/JParserAdapter.h"
#include "org/xml/sax/helpers/JParserFactory.h"
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

                JString* JParserAdapter::FEATURES = new JString("http://xml.org/sax/features/");
                JString* JParserAdapter::NAMESPACES = new JString("http://xml.org/sax/features/namespaces");
                JString* JParserAdapter::NAMESPACE_PREFIXES = new JString("http://xml.org/sax/features/namespace-prefixes");
                JString* JParserAdapter::XMLNS_URIs = new JString("http://xml.org/sax/features/xmlns-uris");

                JParserAdapter::JParserAdapter(JClass* _class):JObject(_class){
                    nsSupport=null;
                    attAdapter=null;
                    parsing = false;
                    nameParts = new JPrimitiveObjectArray(JString::getClazz(),3);
                    parser = null;
                    atts = null;
                    namespaces = true;
                    prefixes = false;
                    uris = false;
                    locator=null;
                    entityResolver = null;
                    dtdHandler = null;
                    contentHandler = null;
                    errorHandler = null;
                }

                JParserAdapter::JParserAdapter():JObject(getClazz()){
                    nsSupport=null;
                    attAdapter=null;
                    parsing = false;
                    nameParts = new JPrimitiveObjectArray(JString::getClazz(),3);
                    parser = null;
                    atts = null;
                    namespaces = true;
                    prefixes = false;
                    uris = false;
                    locator=null;
                    entityResolver = null;
                    dtdHandler = null;
                    contentHandler = null;
                    errorHandler = null;
                    setup(JParserFactory::makeParser());
                }

                JParserAdapter::JParserAdapter(JParser* parser):JObject(getClazz()){
                    nsSupport=null;
                    attAdapter=null;
                    parsing = false;
                    nameParts = new JPrimitiveObjectArray(JString::getClazz(),3);
                    parser = null;
                    atts = null;
                    namespaces = true;
                    prefixes = false;
                    uris = false;
                    locator=null;
                    entityResolver = null;
                    dtdHandler = null;
                    contentHandler = null;
                    errorHandler = null;
                    setup(parser);
                }

                JParserAdapter::JAttributeListAdapter::JAttributeListAdapter(JClass* _class,JParserAdapter* adapter):JObject(_class){
                    this->adapter=adapter;
                    qAtts=null;
                }

                JParserAdapter::JAttributeListAdapter::JAttributeListAdapter(JParserAdapter* adapter):JObject(getClazz()){
                    this->adapter=adapter;
                    qAtts=null;
                }

                void JParserAdapter::JAttributeListAdapter::setAttributeList(JAttributeList* qAtts){
                    this->qAtts=qAtts;
                }

                jint JParserAdapter::JAttributeListAdapter::getLength(){
                    return qAtts->getLength();
                }
                    
                JString* JParserAdapter::JAttributeListAdapter::getURI(jint i){
                    return new JString("");
                }

                JString* JParserAdapter::JAttributeListAdapter::getLocalName(jint i){
                    return new JString("");
                }

                JString* JParserAdapter::JAttributeListAdapter::getQName(jint i){
                    return qAtts->getName(i);
                }

                JString* JParserAdapter::JAttributeListAdapter::getType(jint i){
                    return qAtts->getType(i);
                }

                JString* JParserAdapter::JAttributeListAdapter::getValue(jint i){
                    return qAtts->getValue(i);
                }

                jint JParserAdapter::JAttributeListAdapter::getIndex(JString* uri, JString* localName){
                    return -1;
                }

                jint JParserAdapter::JAttributeListAdapter::getIndex(JString* qName){
                    jint max = adapter->atts->getLength();
                    for (jint i = 0; i < max; i++) {
                        if (qAtts->getName(i)->equals(qName)) {
                            return i;
                        }
                    }
                    return -1;
                }

                JString* JParserAdapter::JAttributeListAdapter::getType(JString* uri, JString* localName){
                    return null;
                }

                JString* JParserAdapter::JAttributeListAdapter::getType(JString* qName){
                    return qAtts->getType(qName);
                }

                JString* JParserAdapter::JAttributeListAdapter::getValue(JString* uri, JString* localName){
                    return null;
                }

                JString* JParserAdapter::JAttributeListAdapter::getValue(JString* qName){
                    return qAtts->getValue(qName);
                }

                JParserAdapter::JAttributeListAdapter::~JAttributeListAdapter(){
                }
                
                void JParserAdapter::setup(JParser* parser){
                    if (parser == null) {
                        throw new JNullPointerException(new JString("Parser argument must not be null"));
                    }
                    this->parser = parser;
                    atts = new JAttributesImpl();
                    nsSupport = new JNamespaceSupport();
                    attAdapter = new JAttributeListAdapter(this);
                }

                void JParserAdapter::setupParser(){
                    if (!prefixes && !namespaces){
                        throw new JIllegalStateException();
                    }
                    nsSupport->reset();
                    if (uris){
                        nsSupport->setNamespaceDeclUris(true);
                    }
                    if (entityResolver != null) {
                        parser->setEntityResolver(entityResolver);
                    }
                    if (dtdHandler != null) {
                        parser->setDTDHandler(dtdHandler);
                    }
                    if (errorHandler != null) {
                        parser->setErrorHandler(errorHandler);
                    }
                    parser->setDocumentHandler(this);
                    locator = null;
                }

                void JParserAdapter::reportError(JString* message){
                    if (errorHandler != null){
                        errorHandler->error(makeException(message));
                    }
                }

                JSAXParseException* JParserAdapter::makeException(JString* message){
                    if (locator != null) {
                        return new JSAXParseException(message);
                    } else {
                        return new JSAXParseException(message, null, null, -1, -1);
                    }
                }

                void JParserAdapter::checkNotParsing(JString* type, JString* name){
                    if (parsing) {
                        throw new JSAXNotSupportedException(name);
                    }
                }

                void JParserAdapter::setFeature(JString* name, jbool value){
                    if (name->equals(NAMESPACES)) {
                        checkNotParsing(new JString("feature"), name);
                        namespaces = value;
                        if (!namespaces && !prefixes) {
                            prefixes = true;
                        }

                    } else if (name->equals(NAMESPACE_PREFIXES)) {
                        checkNotParsing(new JString("feature"), name);
                        prefixes = value;
                        if (!prefixes && !namespaces) {
                            namespaces = true;
                        }

                    } else if (name->equals(XMLNS_URIs)) {
                        checkNotParsing(new JString("feature"), name);
                        uris = value;

                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                jbool JParserAdapter::getFeature(JString* name){
                    if (name->equals(NAMESPACES)) {
                        return namespaces;
                    
                    } else if (name->equals(NAMESPACE_PREFIXES)) {
                        return prefixes;
                    
                    } else if (name->equals(XMLNS_URIs)) {
                        return uris;
                    
                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                void JParserAdapter::setProperty(JString* name, JObject* value){
                    throw new JSAXNotRecognizedException(name);
                }

                JObject* JParserAdapter::getProperty(JString* name){
                    throw new JSAXNotRecognizedException(name);
                }

                void JParserAdapter::setEntityResolver(JEntityResolver* resolver){
                    entityResolver = resolver;
                }

                JEntityResolver* JParserAdapter::getEntityResolver(){
                    return entityResolver;
                }

                void JParserAdapter::setDTDHandler(JDTDHandler* handler){
                    dtdHandler = handler;
                }

                JDTDHandler* JParserAdapter::getDTDHandler(){
                    return dtdHandler;
                }

                void JParserAdapter::setContentHandler(JContentHandler* handler){
                    contentHandler = handler;
                }

                JContentHandler* JParserAdapter::getContentHandler(){
                    return contentHandler;
                }

                void JParserAdapter::setErrorHandler(JErrorHandler* handler){
                    errorHandler = handler;
                }

                JErrorHandler* JParserAdapter::getErrorHandler(){
                    return errorHandler;
                }

                void JParserAdapter::parse(JString* systemId){
                    parse(new JInputSource(systemId));
                }

                void JParserAdapter::parse(JInputSource* input){
                    if (parsing) {
                        throw new JSAXException(new JString("Parser is already in use"));
                    }
                    setupParser();
                    parsing = true;
                    try {
                        parser->parse(input);
                    } catch(JThrowable* th) {
                        parsing = false;
                        throw th;
                    }
                    parsing = false;
                }

                void JParserAdapter::setDocumentLocator(JLocator* locator){
                    this->locator = locator;
                    if (contentHandler != null) {
                        contentHandler->setDocumentLocator(locator);
                    }
                }

                void JParserAdapter::startDocument(){
                    if (contentHandler != null) {
                        contentHandler->startDocument();
                    }
                }

                void JParserAdapter::endDocument(){
                    if (contentHandler != null) {
                        contentHandler->endDocument();
                    }
                }

                void JParserAdapter::startElement(JString* qName, JAttributeList* qAtts){
                    JVector* exceptions = null;
                    if (!namespaces) {
                        if (contentHandler != null) {
                            attAdapter->setAttributeList(qAtts);
                            contentHandler->startElement(new JString(""), new JString(""), qName,attAdapter);
                        }
                        return;
                    }

                    nsSupport->pushContext();
                    jint length = qAtts->getLength();
                    for (jint i = 0; i < length; i++) {
                        JString* attQName = qAtts->getName(i);

                        if (!attQName->startsWith(new JString("xmlns"))){
                            continue;
                        }
                        
                        JString* prefix;
                        jint n = attQName->indexOf(':');
                        if (n == -1 && attQName->length () == 5) {
                            prefix = new JString("");

                        } else if (n != 5) {
                            continue;

                        } else{
                            prefix = attQName->substring(n+1);
                        }

                        JString* value = qAtts->getValue(i);
                        if (!nsSupport->declarePrefix(prefix, value)) {
                            reportError(prefix);
                            continue;
                        }
                        if (contentHandler != null){
                            contentHandler->startPrefixMapping(prefix, value);
                        }
                    }

                    atts->clear();
                    for (jint i = 0; i < length; i++) {
                        JString* attQName = qAtts->getName(i);
                        JString* type = qAtts->getType(i);
                        JString* value = qAtts->getValue(i);

                        if (attQName->startsWith(new JString("xmlns"))) {
                            JString* prefix=null;
                            jint n = attQName->indexOf(':');

                            if (n == -1 && attQName->length () == 5) {
                                prefix = new JString("");

                            } else if (n != 5) {
                                prefix = null;

                            } else {
                                prefix = attQName->substring(6);
                            }

                            if (prefix != null) {
                                if (prefixes) {
                                    if (uris){
                                        atts->addAttribute(nsSupport->XMLNS, prefix,attQName, type, value);
                                    
                                    }else{
                                        atts->addAttribute(new JString(""), new JString(""),attQName, type, value);
                                    }
                                }
                                continue;
                            }
                        }

                        try {
                            JPrimitiveObjectArray* attName = processName(attQName, true, true);
                            atts->addAttribute(dynamic_cast<JString*>(attName->get(0)),
                                              dynamic_cast<JString*>(attName->get(1)),
                                              dynamic_cast<JString*>(attName->get(2)),
                                              type, value);
                        } catch (JSAXException* e) {
                            if (exceptions == null){
                                exceptions = new JVector();
                            }
                            exceptions->addElement(e);
                            atts->addAttribute(new JString(""), attQName, attQName, type, value);
                        }
                    }

                    if (exceptions != null && errorHandler != null) {
                        for (jint i = 0; i < exceptions->size(); i++){
                            errorHandler->error(dynamic_cast<JSAXParseException*>(exceptions->elementAt(i)));
                        }
                    }

                    if (contentHandler != null) {
                        JPrimitiveObjectArray* name = processName(qName, false, false);
                        contentHandler->startElement(dynamic_cast<JString*>(name->get(0)),
                                                     dynamic_cast<JString*>(name->get(1)),
                                                     dynamic_cast<JString*>(name->get(2)),
                                                     atts);
                    }
                }

                void JParserAdapter::endElement(JString* qName){
                    if (!namespaces) {
                        if (contentHandler != null) {
                            contentHandler->endElement(new JString(""), new JString(""), qName);
                        }
                        return;
                    }

                    JPrimitiveObjectArray* names = processName(qName, false, false);
                    if (contentHandler != null) {
                        contentHandler->endElement(dynamic_cast<JString*>(names->get(0)), 
                                                   dynamic_cast<JString*>(names->get(1)),
                                                   dynamic_cast<JString*>(names->get(2)));
                        JEnumeration* prefixes = nsSupport->getDeclaredPrefixes();
                        while (prefixes->hasMoreElements()) {
                            JString* prefix = dynamic_cast<JString*>(prefixes->nextElement());
                            contentHandler->endPrefixMapping(prefix);
                        }
                    }
                    nsSupport->popContext();
                }

                void JParserAdapter::characters(JPrimitiveCharArray* ch, jint start, jint length){
                    if (contentHandler != null) {
                        contentHandler->characters(ch, start, length);
                    }
                }

                void JParserAdapter::ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length){
                    if (contentHandler != null) {
                        contentHandler->ignorableWhitespace(ch, start, length);
                    }
                }

                void JParserAdapter::processingInstruction(JString* target, JString* data){
                    if (contentHandler != null) {
                        contentHandler->processingInstruction(target, data);
                    }
                }

                JPrimitiveObjectArray* JParserAdapter::processName(JString* qName, jbool isAttribute,jbool useException){
                    JPrimitiveObjectArray* parts = nsSupport->processName(qName, nameParts,isAttribute);
                    if (parts == null) {
                        if (useException){
                            throw makeException(qName);
                        }
                        reportError(qName);
                        parts = new JPrimitiveObjectArray(JString::getClazz(),3);
                        parts->set(0,new JString());
                        parts->set(1,parts->get(0));
                        parts->set(2, qName);
                    }
                    return parts;
                }
                
                JParserAdapter::~JParserAdapter(){
                }
            }
        }
    }
}
