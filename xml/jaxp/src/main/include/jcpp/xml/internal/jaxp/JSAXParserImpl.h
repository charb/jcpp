#ifndef JCPP_XML_INTERNAL_JAXP_DOCUMENT_SAXPARSER_IMPL_H
#define JCPP_XML_INTERNAL_JAXP_DOCUMENT_SAXPARSER_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JHashtable.h"
#include "org/xml/sax/JXMLReader.h"
#include "jcpp/xml/parsers/JSAXParser.h"

using namespace org::xml::sax;
using namespace jcpp::xml::parsers;
using namespace jcpp::util;

namespace jcpp{
    namespace xml{
        namespace parsers{
            class JSAXParserFactory;
        }
        namespace internal{
            namespace jaxp{

            	// @Class(canonicalName="javax.xml.internal.jaxp.SAXParserImpl", simpleName="SAXParserImpl");
                class JCPP_EXPORT JSAXParserImpl : public JSAXParser{
                protected:
                    JXMLReader* xmlReader;
                    JParser* parser;
                    jbool validating;
                    jbool namespaceAware;
    
                public:
                    JSAXParserImpl(JSAXParserFactory* spf, JHashtable* features);

                    static JClass* getClazz();

                    virtual void setFeatures(JHashtable* features);

                    virtual JParser* getParser();

                    virtual JXMLReader* getXMLReader();

                    virtual jbool isNamespaceAware();

                    virtual jbool isValidating();

                    virtual void setProperty(JString* name, JObject* value);

                    virtual JObject* getProperty(JString* name);

                    virtual ~JSAXParserImpl();
                };
            }
        }
    }
}

#endif
