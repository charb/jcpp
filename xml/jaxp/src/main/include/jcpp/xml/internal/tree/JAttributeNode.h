#ifndef JCPP_XML_INTERNAL_TREE_ATTRIBUTE_NODE_H
#define JCPP_XML_INTERNAL_TREE_ATTRIBUTE_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JNamespacedNode.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JElement.h"
#include "org/w3c/dom/JAttr.h"
#include "org/w3c/dom/JTypeInfo.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.AttributeNode", simpleName="AttributeNode");
                class JCPP_EXPORT JAttributeNode : public JNamespacedNode, public virtual JAttr{
                protected:
                    JString* value;
                    jbool specified;
                    JString* defaultValue;
                    JElement* ownerElement;
                    JAttributeNode(JClass* _class,JString* namespaceURI, JString* qName,JString* value, jbool specified, JString* defaultValue);

                public:
                    JAttributeNode(JString* namespaceURI, JString* qName,JString* value, jbool specified, JString* defaultValue);

                    static JClass* getClazz();

                    virtual JAttributeNode* makeClone();

                    static void checkArguments(JString* namespaceURI, JString* qualifiedName);

                    virtual JString* getDefaultValue();

                    virtual JElement* getOwnerElement();

                    virtual void setOwnerElement(JElement* element);

                    virtual jshort getNodeType();

                    virtual JString* getName();

                    virtual JString* getValue();

                    virtual void setValue(JString* value);

                    virtual JString* getNodeValue();

                    virtual jbool getSpecified();

                    virtual void setNodeValue(JString* value);

                    virtual void setSpecified(jbool specified);

                    virtual JNode* getParentNode();

                    virtual JNode* getNextSibling();

                    virtual JNode* getPreviousSibling();

                    virtual void writeXml(JXmlWriteContext* context);

                    virtual void writeChildrenXml(JXmlWriteContext* context);

                    virtual JNode* cloneNode(jbool deep);

                    virtual JAttributeNode* cloneAttributeNode(jbool deep);

                    virtual void checkChildType(jint type);

                    virtual JTypeInfo* getSchemaTypeInfo();

                    virtual jbool isId();

                    virtual ~JAttributeNode();
                };
            }
        }
    }
}

#endif
