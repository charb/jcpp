#ifndef ORG_W3C_DOM_NODE_H
#define ORG_W3C_DOM_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace org{
    namespace w3c{
        namespace dom{
            class JNodeList;
            class JDocument;
            class JNamedNodeMap;
            class JUserDataHandler;

            // @Class(canonicalName="org.w3c.dom.Node", simpleName="Node");
            class JCPP_EXPORT JNode : public JInterface{
            public:
                static JClass* getClazz();

                static const jshort ELEMENT_NODE=1;                
                static const jshort ATTRIBUTE_NODE=2;
                static const jshort TEXT_NODE=3;
                static const jshort CDATA_SECTION_NODE=4;
                static const jshort ENTITY_REFERENCE_NODE=5;
                static const jshort ENTITY_NODE=6;
                static const jshort PROCESSING_INSTRUCTION_NODE=7;
                static const jshort COMMENT_NODE=8;
                static const jshort DOCUMENT_NODE=9;
                static const jshort DOCUMENT_TYPE_NODE=10;
                static const jshort DOCUMENT_FRAGMENT_NODE=11;
                static const jshort NOTATION_NODE=12;
                static const jshort DOCUMENT_POSITION_DISCONNECTED=0x01;
                static const jshort DOCUMENT_POSITION_PRECEDING=0x02;
                static const jshort DOCUMENT_POSITION_FOLLOWING=0x04;
                static const jshort DOCUMENT_POSITION_CONTAINS=0x08;
                static const jshort DOCUMENT_POSITION_CONTAINED_BY=0x10;
                static const jshort DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC=0x20;

                virtual JString* getNodeName()=0;

                virtual JString* getNodeValue()=0;

                virtual void setNodeValue(JString* nodeValue)=0;

                virtual jshort getNodeType()=0;

                virtual JNode* getParentNode()=0;

                virtual JNodeList* getChildNodes()=0;

                virtual JNode* getFirstChild()=0;

                virtual JNode* getLastChild()=0;
    
                virtual JNode* getPreviousSibling()=0;

                virtual JNode* getNextSibling()=0;

                virtual JNamedNodeMap* getAttributes()=0;

                virtual JDocument* getOwnerDocument()=0;

                virtual JNode* insertBefore(JNode* newChild,JNode* refChild)=0;

                virtual JNode* replaceChild(JNode* newChild,JNode* oldChild)=0;

                virtual JNode* removeChild(JNode* oldChild)=0;
    
                virtual JNode* appendChild(JNode* newChild)=0;

                virtual jbool hasChildNodes()=0;

                virtual JNode* cloneNode(jbool deep)=0;

                virtual void normalize()=0;

                virtual jbool isSupported(JString* feature,JString* version)=0;

                virtual JString* getNamespaceURI()=0;

                virtual JString* getPrefix()=0;

                virtual void setPrefix(JString* prefix)=0;

                virtual JString* getLocalName()=0;

                virtual jbool hasAttributes()=0;

                virtual JString* getBaseURI()=0;

                virtual jshort compareDocumentPosition(JNode* other)=0;

                virtual JString* getTextContent()=0;

                virtual void setTextContent(JString* textContent)=0;

                virtual jbool isSameNode(JNode* other)=0;

                virtual JString* lookupPrefix(JString* namespaceURI)=0;

                virtual jbool isDefaultNamespace(JString* namespaceURI)=0;

                virtual JString* lookupNamespaceURI(JString* prefix)=0;

                virtual jbool isEqualNode(JNode* arg)=0;

                virtual JObject* getFeature(JString* feature,JString* version)=0;

                virtual JObject* setUserData(JString* key,JObject* data,JUserDataHandler* handler)=0;

                virtual JObject* getUserData(JString* key)=0;

                virtual ~JNode();
            };
        }
    }
}

#endif
