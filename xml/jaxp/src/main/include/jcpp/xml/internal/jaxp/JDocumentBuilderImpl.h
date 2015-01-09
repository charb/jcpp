#ifndef JCPP_XML_INTERNAL_JAXP_DOCUMENT_BUILDER_IMPL_H
#define JCPP_XML_INTERNAL_JAXP_DOCUMENT_BUILDER_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/parser/JAttributesEx.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JXMLReader.h"
#include "org/xml/sax/JInputSource.h"
#include "org/w3c/dom/JDOMImplementation.h"
#include "org/w3c/dom/JDocument.h"
#include "jcpp/xml/parsers/JDocumentBuilder.h"
#include "jcpp/xml/internal/tree/JXmlDocumentBuilder.h"
#include "jcpp/xml/internal/tree/JXmlDocumentBuilderNS.h"
#include "jcpp/xml/internal/tree/JDOMImplementationImpl.h"

using namespace jcpp::xml::internal::tree;
using namespace org::xml::sax;
using namespace org::w3c::dom;
using namespace jcpp::xml::parsers;

namespace jcpp{
    namespace xml{
        namespace parsers{
            class JDocumentBuilderFactory;
        }
        namespace internal{
            namespace jaxp{

            	// @Class(canonicalName="javax.xml.internal.jaxp.DocumentBuilderImpl", simpleName="DocumentBuilderImpl");
                class JCPP_EXPORT JDocumentBuilderImpl : public JDocumentBuilder{
                protected:
                    JDocumentBuilderFactory* dbf;
                    JEntityResolver* er;
                    JErrorHandler* eh;
                    JXMLReader* xmlReader;
                    JXmlDocumentBuilder* builder;
                    jbool namespaceAware;
                    jbool validating;

                public:
                    JDocumentBuilderImpl(JDocumentBuilderFactory* dbf);

                    static JClass* getClazz();

                    virtual JDocument* newDocument();

                    virtual JDOMImplementation* getDOMImplementation();

                    virtual JDocument* parse(JInputSource* is);

                    virtual jbool isNamespaceAware();

                    virtual jbool isValidating();

                    virtual void setEntityResolver(JEntityResolver* er);

                    virtual void setErrorHandler(JErrorHandler* eh);

                    virtual ~JDocumentBuilderImpl();
                };
            }
        }
    }
}

#endif
