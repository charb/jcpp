#include "jcpp/xml/internal/jaxp/JDocumentBuilderImpl.h"
#include "jcpp/xml/internal/parser/JXMLReaderImpl.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/helpers/JDefaultHandler.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/xml/internal/jaxp/JDocumentBuilderFactoryImpl.h"
#include "jcpp/xml/parsers/JDocumentBuilderFactory.h"
#include "jcpp/xml/internal/jaxp/JDefaultValidationErrorHandler.h"

using namespace jcpp::xml::internal::parser;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace jaxp{

                JDocumentBuilderImpl::JDocumentBuilderImpl(JDocumentBuilderFactory* dbf):JDocumentBuilder(getClazz()){
                    er=null;
                    eh=null;
                    this->dbf = dbf;
                    namespaceAware = dbf->isNamespaceAware();

                    xmlReader = new JXMLReaderImpl();

                    validating = dbf->isValidating();
                    JString* validation = new JString("http://xml.org/sax/features/validation");
                    xmlReader->setFeature(validation, validating);

                    if (validating) {
                        setErrorHandler(new JDefaultValidationErrorHandler());
                    }

                    JString* nsPrefixes = new JString("http://xml.org/sax/features/namespace-prefixes");
                    xmlReader->setFeature(nsPrefixes, true);

                    JString* namespaces = new JString("http://xml.org/sax/features/namespaces");
                    xmlReader->setFeature(namespaces, namespaceAware);

                    if (namespaceAware) {
                        builder = new JXmlDocumentBuilderNS();
                    } else {
                        builder = new JXmlDocumentBuilder();
                    }

                    xmlReader->setContentHandler(builder);
                  
                    JString* lexHandler = new JString("http://xml.org/sax/properties/lexical-handler");
                    xmlReader->setProperty(lexHandler, builder);

                    JString* declHandler =new JString("http://xml.org/sax/properties/declaration-handler");
                    xmlReader->setProperty(declHandler, builder);

                    xmlReader->setDTDHandler(builder);

                    builder->setIgnoreWhitespace(dbf->isIgnoringElementContentWhitespace());
                    builder->setExpandEntityReferences(dbf->isExpandEntityReferences());
                    builder->setIgnoreComments(dbf->isIgnoringComments());
                    builder->setPutCDATAIntoText(dbf->isCoalescing());
                }

                JDocument* JDocumentBuilderImpl::newDocument(){
                    return new JXmlDocument(); 
                }

                JDOMImplementation* JDocumentBuilderImpl::getDOMImplementation(){
                    return JDOMImplementationImpl::getDOMImplementation(); 
                }

                JDocument* JDocumentBuilderImpl::parse(JInputSource* is){
                    if (is == null) {
                        throw new JIllegalArgumentException(new JString("InputSource cannot be null"));
                    }

                    if (er != null) {
                        xmlReader->setEntityResolver(er);
                    }

                    if (eh != null) {
                        xmlReader->setErrorHandler(eh);      
                    }

                    xmlReader->parse(is);
                    return builder->getDocument();
                }

                jbool JDocumentBuilderImpl::isNamespaceAware(){
                    return namespaceAware;
                }

                jbool JDocumentBuilderImpl::isValidating(){
                    return validating;
                }

                void JDocumentBuilderImpl::setEntityResolver(JEntityResolver* er){
                    this->er = er;
                }

                void JDocumentBuilderImpl::setErrorHandler(JErrorHandler* eh){
                    this->eh = (eh == null) ? new JDefaultHandler() : eh;
                }

                JDocumentBuilderImpl::~JDocumentBuilderImpl(){
                }
            }
        }
    }
}
