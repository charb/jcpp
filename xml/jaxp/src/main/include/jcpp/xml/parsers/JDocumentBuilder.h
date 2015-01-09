#ifndef JCPP_XML_PARSERS_DOCUMENT_BUILDER_H
#define JCPP_XML_PARSERS_DOCUMENT_BUILDER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JFile.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JDOMImplementation.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JErrorHandler.h"

using namespace jcpp::io;
using namespace org::w3c::dom;
using namespace org::xml::sax;

namespace jcpp{
    namespace xml{
        namespace parsers{            

        	// @Class(canonicalName="javax.xml.parsers.DocumentBuilder", simpleName="DocumentBuilder");
            class JCPP_EXPORT JDocumentBuilder : public JObject{
            protected:
                JDocumentBuilder(JClass* _class);

            public:
                static JClass* getClazz();

                virtual void reset();

                virtual JDocument* parse(JInputStream* is);

                virtual JDocument* parse(JInputStream* is, JString* systemId);

                virtual JDocument* parse(JString* uri);

                virtual JDocument* parse(JFile* f);

                virtual JDocument* parse(JInputSource* is)=0;

                virtual jbool isNamespaceAware()=0;

                virtual jbool isValidating()=0;

                virtual void setEntityResolver(JEntityResolver* er)=0;

                virtual void setErrorHandler(JErrorHandler* eh)=0;

                virtual JDocument* newDocument()=0;

                virtual JDOMImplementation* getDOMImplementation()=0;

                virtual jbool isXIncludeAware();

                virtual ~JDocumentBuilder();
            };
        }
    }
}

#endif
