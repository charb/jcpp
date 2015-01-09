#ifndef JCPP_XML_INTERNAL_TREE_XML_DOCUMENT_BUILDER_NS_H
#define JCPP_XML_INTERNAL_TREE_XML_DOCUMENT_BUILDER_NS_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JXmlDocumentBuilder.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.XmlDocumentBuilderNS", simpleName="XmlDocumentBuilderNS");
                class JCPP_EXPORT JXmlDocumentBuilderNS : public JXmlDocumentBuilder{
                public:
                    JXmlDocumentBuilderNS();

                    static JClass* getClazz();

                    virtual void startElement(JString* namespaceURI, JString* localName,JString* qName, JAttributes* attributes);

                    virtual void processingInstruction(JString* name, JString* instruction);

                    virtual void internalEntityDecl(JString* name, JString* value);

                    virtual void externalEntityDecl(JString* name, JString* publicId,JString* systemId);

                    virtual void notationDecl(JString* n, JString* p, JString* s);

                    virtual void unparsedEntityDecl(JString* name, JString* publicId, JString* systemId, JString* notation);
                    
                    virtual ~JXmlDocumentBuilderNS();
                };
            }
        }
    }
}

#endif
