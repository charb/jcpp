#ifndef JCPP_XML_PARSERS_SAX_PARSER_FACTORY_H
#define JCPP_XML_PARSERS_SAX_PARSER_FACTORY_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JFile.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JDOMImplementation.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JErrorHandler.h"
#include "jcpp/xml/parsers/JSAXParser.h"

using namespace jcpp::io;
using namespace org::w3c::dom;
using namespace org::xml::sax;

namespace jcpp{
    namespace xml{
        namespace parsers{

        	// @Class(canonicalName="javax.xml.parsers.SAXParserFactory", simpleName="SAXParserFactory");
            class JCPP_EXPORT JSAXParserFactory : public JObject{
            protected:
                jbool validating;
                jbool namespaceAware;
                JSAXParserFactory(JClass* _class);

            public:
                static JClass* getClazz();

                static JSAXParserFactory* newInstance();

                static JSAXParserFactory* newInstance(JString* factoryClassName, JClassLoader* classLoader);

                virtual JSAXParser* newSAXParser()=0;
          
                virtual void setNamespaceAware(jbool awareness);

                virtual void setValidating(jbool validating);

                virtual jbool isNamespaceAware();

                virtual jbool isValidating();

                virtual void setFeature(JString* name, jbool value)=0;

                virtual jbool getFeature(JString* name)=0;

                virtual void setXIncludeAware(jbool state);

                virtual jbool isXIncludeAware();

                virtual ~JSAXParserFactory();
            };
        }
    }
}

#endif
