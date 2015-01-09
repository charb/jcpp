#ifndef JCPP_XML_INTERNAL_TREE_NODE_BASE_H
#define JCPP_XML_INTERNAL_TREE_NODE_BASE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "jcpp/xml/internal/tree/JNodeEx.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JNamedNodeMap.h"
#include "org/w3c/dom/JUserDataHandler.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{
                class JParentNode;
                class JXmlDocument;

                // @Class(canonicalName="javax.xml.internal.tree.NodeBase", simpleName="NodeBase");
                class JCPP_EXPORT JNodeBase : public JObject, public virtual JNodeEx, public virtual JNodeList{
                protected:
                    JParentNode* parent;
                    jint parentIndex;
                    JXmlDocument* ownerDocument;
                    jbool readonly;
                    JNodeBase(JClass* _class);

                public:
                    static JClass* getClazz();

                    virtual JParentNode* getParentImpl();

                    virtual jbool isReadonly();

                    virtual void setReadonly(jbool deep);

                    virtual JString* getLanguage();

                    virtual JString* getInheritedAttribute(JString* name);

                    virtual void writeChildrenXml(JXmlWriteContext* context);

                    virtual JNode* getParentNode();

                    virtual void setParentNode(JParentNode* arg, jint index);

                    virtual void setOwnerDocument(JXmlDocument* doc);

                    virtual JDocument* getOwnerDocument();

                    virtual jbool hasChildNodes();

                    virtual void setNodeValue(JString* value);

                    virtual JString* getNodeValue();

                    virtual JNode* getFirstChild();

                    virtual jint getLength();

                    virtual JNode* item(jint i);

                    virtual JNodeList* getChildNodes();

                    virtual JNode* getLastChild();

                    virtual JNode* appendChild(JNode* newChild);

                    virtual JNode* insertBefore(JNode* newChild, JNode* refChild);

                    virtual JNode* replaceChild(JNode* newChild, JNode* refChild);

                    virtual JNode* removeChild(JNode* oldChild);

                    virtual JNode* getNextSibling();

                    virtual JNode* getPreviousSibling();

                    virtual JNamedNodeMap* getAttributes();

                    virtual void normalize();

                    virtual jbool isSupported(JString* feature, JString* version);

                    virtual JString* getNamespaceURI();

                    virtual JString* getPrefix();

                    virtual void setPrefix(JString* prefix);

                    virtual JString* getLocalName();

                    virtual JString* getBaseURI();

                    virtual jshort compareDocumentPosition(JNode* other);

                    virtual JString* getTextContent();

                    virtual void setTextContent(JString* textContent);

                    virtual jbool isSameNode(JNode* other);

                    virtual JString* lookupPrefix(JString* namespaceURI);

                    virtual jbool isDefaultNamespace(JString* namespaceURI);

                    virtual JString* lookupNamespaceURI(JString* prefix);

                    virtual jbool isEqualNode(JNode* arg);

                    virtual JObject* getFeature(JString* feature,JString* version);

                    virtual JObject* setUserData(JString* key,JObject* data,JUserDataHandler* handler);

                    virtual JObject* getUserData(JString* key);

                    virtual jbool hasAttributes();

                    virtual jint getIndexOf(JNode* maybeChild);

                    virtual ~JNodeBase();
                };
            }
        }
    }
}

#endif
