#ifndef JCPP_XML_PARSERS_SAX_PARSER_H
#define JCPP_XML_PARSERS_SAX_PARSER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JFile.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JDOMImplementation.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JHandlerBase.h"
#include "org/xml/sax/helpers/JDefaultHandler.h"
#include "org/xml/sax/JXMLReader.h"
#include "org/xml/sax/JParser.h"

using namespace jcpp::io;
using namespace org::w3c::dom;
using namespace org::xml::sax;
using namespace org::xml::sax::helpers;

namespace jcpp{
    namespace xml{
        namespace parsers{

        	// @Class(canonicalName="javax.xml.parsers.SAXParser", simpleName="SAXParser");
            class JCPP_EXPORT JSAXParser : public JObject{
            protected:
                JSAXParser(JClass* _class);

            public:
                static JClass* getClazz();

                virtual void reset();

                virtual void parse(JInputStream* is, JHandlerBase* hb);

                virtual void parse(JInputStream* is,JHandlerBase* hb,JString* systemId);

                virtual void parse(JInputStream* is, JDefaultHandler* dh);

                virtual void parse(JInputStream* is, JDefaultHandler* dh, JString* systemId);

                virtual void parse(JString* uri, JHandlerBase* hb);

                virtual void parse(JString* uri, JDefaultHandler* dh);

                virtual void parse(JFile* f, JHandlerBase* hb);

                virtual void parse(JFile* f, JDefaultHandler* dh);

                virtual void parse(JInputSource* is, JHandlerBase* hb);

                virtual void parse(JInputSource* is, JDefaultHandler* dh);

                virtual JParser* getParser()=0;

                virtual JXMLReader* getXMLReader()=0;

                virtual jbool isNamespaceAware()=0;

                virtual jbool isValidating()=0;

                virtual void setProperty(JString* name, JObject* value)=0;

                virtual JObject* getProperty(JString* name)=0;

                virtual jbool isXIncludeAware();

                virtual ~JSAXParser();
            };
        }
    }
}

#endif
