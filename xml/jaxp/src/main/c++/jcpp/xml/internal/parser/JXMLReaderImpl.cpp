#include "jcpp/xml/internal/parser/JXMLReaderImpl.h"
#include "jcpp/xml/internal/parser/JParser2.h"
#include "jcpp/xml/internal/parser/JValidatingParser.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/io/JFileInputStream.h"
#include "jcpp/io/JInputStreamReader.h"
#include "org/xml/sax/JSAXNotRecognizedException.h"
#include "org/xml/sax/JSAXException.h"
#include "org/xml/sax/JSAXNotSupportedException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JString* JXMLReaderImpl::FEATURES = new JString("http://xml.org/sax/features/");
                JString* JXMLReaderImpl::NAMESPACES = new JString("http://xml.org/sax/features/namespaces");
                JString* JXMLReaderImpl::NAMESPACE_PREFIXES = new JString("http://xml.org/sax/features/namespace-prefixes");
                JString* JXMLReaderImpl::STRING_INTERNING = new JString("http://xml.org/sax/features/string-interning") ;
                JString* JXMLReaderImpl::VALIDATION = new JString("http://xml.org/sax/features/validation");
                JString* JXMLReaderImpl::EXTERNAL_GENERAL = new JString("http://xml.org/sax/features/external-general-entities");
                JString* JXMLReaderImpl::EXTERNAL_PARAMETER = new JString("http://xml.org/sax/features/external-parameter-entities");
                JString* JXMLReaderImpl::LEXICAL_PARAMETER_ENTITIES = new JString("http://xml.org/sax/features/lexical-handler/parameter-entities");
                JString* JXMLReaderImpl::PROPERTIES = new JString("http://xml.org/sax/properties/");
                JString* JXMLReaderImpl::LEXICAL_HANDLER = new JString("http://xml.org/sax/properties/lexical-handler");
                JString* JXMLReaderImpl::DECLARATION_HANDLER = new JString("http://xml.org/sax/properties/declaration-handler");

                JXMLReaderImpl::JXMLReaderImpl(){
                    namespaces=true;
                    prefixes=false;
                    validation=false;
                    lexicalHandler=null;
                    declHandler=null;
                    contentHandler=null;
                    dtdHandler=null;
                    errorHandler=null;
                    entityResolver=null;
                    parser=null;
                    parsing=false;  
                }

                jbool JXMLReaderImpl::getFeature(JString* name){
                    if (name->equals(NAMESPACES)) {
                        return namespaces;

                    } else if (name->equals(NAMESPACE_PREFIXES)) {
                        return prefixes;

                    } else if (name->equals(VALIDATION)) {
                        return validation;

                    } else if (name->equals(STRING_INTERNING) ||
                               name->equals(EXTERNAL_GENERAL) ||
                               name->equals(EXTERNAL_PARAMETER)) {
                        return true;

                    } else if (name->equals(LEXICAL_PARAMETER_ENTITIES)) {
                        return false;

                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                void JXMLReaderImpl::setFeature(JString* name, jbool state){
                    if (name->equals(NAMESPACES)) {
                        checkNotParsing(new JString("feature"), name);
                        namespaces = state;
                        if (!namespaces && !prefixes) {
                            prefixes = true;
                        }

                    } else if (name->equals(NAMESPACE_PREFIXES)) {
                        checkNotParsing(new JString("feature"), name);
                        prefixes = state;
                        if (!prefixes && !namespaces) {
                            namespaces = true;
                        }

                    } else if (name->equals(VALIDATION)) {
                        checkNotParsing(new JString("feature"), name);
                        if (validation != state) {
                            parser = null;
                        }
                        validation = state;

                    } else if (name->equals(STRING_INTERNING) ||
                               name->equals(EXTERNAL_GENERAL) ||
                               name->equals(EXTERNAL_PARAMETER)) {
                        
                        checkNotParsing(new JString("feature"), name);
                        if (state == false) {
                            throw new JSAXNotSupportedException(name);
                        }

                    } else if (name->equals(LEXICAL_PARAMETER_ENTITIES)) {
                        checkNotParsing(new JString("feature"), name);
                        if (state == true) {
                            throw new JSAXNotSupportedException(name);
                        }

                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                JObject* JXMLReaderImpl::getProperty(JString* name){
                    if (name->equals(LEXICAL_HANDLER)) {
                        return dynamic_cast<JObject*>(lexicalHandler);
                    
                    } else if (name->equals(DECLARATION_HANDLER)) {
                        return dynamic_cast<JObject*>(declHandler);
                    
                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                void JXMLReaderImpl::setProperty(JString* name, JObject* value){
                    if (name->equals(LEXICAL_HANDLER)) {
                        if (!(value->isInstanceOf(JLexicalHandler::getClazz()))) {
                            throw new JSAXNotSupportedException(name);
                        }
                        lexicalHandler = dynamic_cast<JLexicalHandler*>(value);

                    } else if (name->equals(DECLARATION_HANDLER)) {
                        if (!(value->isInstanceOf(JDeclHandler::getClazz()))) {
                            throw new JSAXNotSupportedException(name);
                        }
                        declHandler = dynamic_cast<JDeclHandler*>(value);

                    } else {
                        throw new JSAXNotRecognizedException(name);
                    }
                }

                void JXMLReaderImpl::setEntityResolver(JEntityResolver* resolver){
                    if (resolver == null) {
                        throw new JNullPointerException(new JString("Null entity resolver"));
                    }
                    entityResolver = resolver;
                    if (parser != null) {
                        parser->setEntityResolver(resolver); 
                    }
                }

                JEntityResolver* JXMLReaderImpl::getEntityResolver(){
                    return entityResolver;
                }

                void JXMLReaderImpl::setDTDHandler(JDTDHandler* handler){
                    if (handler == null) {
                        throw new JNullPointerException(new JString("Null DTD handler"));
                    }
                    dtdHandler = handler;
                    if (parser != null) {
                        parser->setDTDHandler(dtdHandler);
                    }
                }

                JDTDHandler* JXMLReaderImpl::getDTDHandler(){
                    return dtdHandler;
                }

                void JXMLReaderImpl::setContentHandler(JContentHandler* handler){
                    if (handler == null) {
                        throw new JNullPointerException(new JString("Null content handler"));
                    }
                    contentHandler = handler;
                    if (parser != null) {
                        parser->setContentHandler(handler);
                    }
                }

                JContentHandler* JXMLReaderImpl::getContentHandler(){
                    return contentHandler;
                }

                void JXMLReaderImpl::setErrorHandler(JErrorHandler* handler){
                    if (handler == null) {
                        throw new JNullPointerException(new JString("Null error handler"));
                    }
                    errorHandler = handler;
                    if (parser != null) {
                        parser->setErrorHandler(errorHandler);
                    }
                }

                JErrorHandler* JXMLReaderImpl::getErrorHandler(){
                    return errorHandler;
                }

                void JXMLReaderImpl::parse(JString* systemId){
                    parse(new JInputSource(systemId));
                }

                void JXMLReaderImpl::parse(JInputSource* input){
                    if (parsing) {
                        throw new JSAXException(new JString("Parser is already in use"));
                    }
                    parsing = true;

                    if (parser == null) {
                        if (validation) {
                            parser = new JValidatingParser();
                        } else {
                            parser = new JParser2();
                        }
                    }

                    parser->setNamespaceFeatures(namespaces, prefixes);
                    parser->setContentHandler(contentHandler);
                    parser->setDTDHandler(dtdHandler);
                    parser->setErrorHandler(errorHandler);
                    parser->setEntityResolver(entityResolver);
                    parser->setLexicalHandler(lexicalHandler);
                    parser->setDeclHandler(declHandler);

                    JThrowable* th2=null;
                    try {
                        parser->parse(input);
                    } catch(JThrowable* th){
                        th2=th;                        
                    }
                    parsing = false;
                    if (th2!=null){
                        throw th2;
                    }
                }

                void JXMLReaderImpl::checkNotParsing(JString* type, JString* name){
                    if (parsing) {
                        throw new JSAXNotSupportedException(new JString("Cannot change parameter while parsing"));
                    }
                }

                JXMLReaderImpl::~JXMLReaderImpl(){
                }
            }
        }
    }
}
