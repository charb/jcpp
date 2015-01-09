#include "jcpp/xml/internal/jaxp/JSAXParserImpl.h"
#include "jcpp/xml/internal/parser/JXMLReaderImpl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JBoolean.h"
#include "org/xml/sax/helpers/JXMLReaderAdapter.h"
#include "org/xml/sax/JHandlerBase.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/xml/internal/jaxp/JSAXParserFactoryImpl.h"
#include "jcpp/xml/parsers/JSAXParserFactory.h"
#include "jcpp/xml/internal/jaxp/JDefaultValidationErrorHandler.h"

using namespace jcpp::xml::internal::parser;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace jaxp{

                JSAXParserImpl::JSAXParserImpl(JSAXParserFactory* spf, JHashtable* features):JSAXParser(getClazz()){
                    parser=null;
                    xmlReader = new JXMLReaderImpl();
                    validating = spf->isValidating();
                    
                    JString* validation = new JString("http://xml.org/sax/features/validation");

                    if (validating) {
                        xmlReader->setErrorHandler(new JDefaultValidationErrorHandler());
                    }

                    xmlReader->setFeature(validation, validating);

                    namespaceAware = spf->isNamespaceAware();
                    JString* namespaces = new JString("http://xml.org/sax/features/namespaces");
                    xmlReader->setFeature(namespaces, namespaceAware);

                    if (namespaceAware == false) {
                        JString* prefixes = new JString("http://xml.org/sax/features/namespace-prefixes");
                        xmlReader->setFeature(prefixes, true);
                    }
                    setFeatures(features);
                }

                void JSAXParserImpl::setFeatures(JHashtable* features){
                    if (features != null) {
                        for (JEnumeration* e = features->keys(); e->hasMoreElements();) {
                            JString* feature = dynamic_cast<JString*>(e->nextElement());
                            jbool value = (dynamic_cast<JBoolean*>(features->get(feature)))->booleanValue();
                            xmlReader->setFeature(feature, value);
                        }
                    }
                }

                JParser* JSAXParserImpl::getParser(){
                    if (parser == null) {
                        parser = new JXMLReaderAdapter(xmlReader);
                        parser->setDocumentHandler(new JHandlerBase());
                    }
                    return parser;
                }

                JXMLReader* JSAXParserImpl::getXMLReader(){
                    return xmlReader;
                }

                jbool JSAXParserImpl::isNamespaceAware(){
                    return namespaceAware;
                }

                jbool JSAXParserImpl::isValidating(){
                    return validating;
                }

                void JSAXParserImpl::setProperty(JString* name, JObject* value){
                    xmlReader->setProperty(name, value);
                }

                JObject* JSAXParserImpl::getProperty(JString* name){
                    return xmlReader->getProperty(name);
                }

                JSAXParserImpl::~JSAXParserImpl(){
                }
            }
        }
    }
}
