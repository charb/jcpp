#ifndef JCPP_XML_INTERNAL_JAXP_DOCUMENT_BUILDER_FACTORY_IMPL_H
#define JCPP_XML_INTERNAL_JAXP_DOCUMENT_BUILDER_FACTORY_IMPL_H

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
#include "jcpp/xml/parsers/JDocumentBuilderFactory.h"
#include "jcpp/xml/internal/tree/JXmlDocumentBuilder.h"
#include "jcpp/xml/internal/tree/JXmlDocumentBuilderNS.h"
#include "jcpp/xml/internal/tree/JDOMImplementationImpl.h"

using namespace jcpp::xml::internal::tree;
using namespace org::xml::sax;
using namespace org::w3c::dom;
using namespace jcpp::xml::parsers;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace jaxp{

            	// @Class(canonicalName="javax.xml.internal.jaxp.DocumentBuilderFactoryImpl", simpleName="DocumentBuilderFactoryImpl");
                class JCPP_EXPORT JDocumentBuilderFactoryImpl : public JDocumentBuilderFactory{
                public:
                    JDocumentBuilderFactoryImpl();

                    static JClass* getClazz();

                    virtual JDocumentBuilder* newDocumentBuilder();
                    
                    virtual void setAttribute(JString* name, JObject* value);

                    virtual JObject* getAttribute(JString* name);

                    virtual void setFeature(JString* name, jbool value);

                    virtual jbool getFeature(JString* name);

                    virtual ~JDocumentBuilderFactoryImpl();
                };
            }
        }
    }
}

#endif
