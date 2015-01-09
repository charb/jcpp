#ifndef JCPP_XML_INTERNAL_TREE_ELEMENT_NODE2_H
#define JCPP_XML_INTERNAL_TREE_ELEMENT_NODE2_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JNamespacedNode.h"
#include "jcpp/xml/internal/tree/JElementEx.h"
#include "jcpp/xml/internal/tree/JAttributeSet.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JNamedNodeMap.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.ElementNode2", simpleName="ElementNode2");
                class JCPP_EXPORT JElementNode2 : public JNamespacedNode, public virtual JElementEx{
                protected:
                    static JPrimitiveCharArray* tagStart;
                    static JPrimitiveCharArray* getTagStart();
                    static JPrimitiveCharArray* tagEnd;
                    static JPrimitiveCharArray* getTagEnd();
                    JAttributeSet* attributes;
                    JString* idAttributeName;
                    JObject* userObject;
                    JElementNode2(JClass* _class,JString* namespaceURI,JString* qName);
                    friend class JElementNode;
                    friend class JXmlDocument;

                public:
                    JElementNode2(JString* namespaceURI,JString* qName);

                    static void checkArguments(JString* namespaceURI, JString* qualifiedName);
                    
                    static JClass* getClazz();

                    virtual JElementNode2* makeClone();

                    virtual JElementNode2* createCopyForImportNode(jbool deep);

                    virtual void trimToSize();

                    virtual void setAttributes(JAttributeSet* a);

                    virtual void checkChildType(jint type);

                    virtual void setReadonly(jbool deep);

                    virtual JNamedNodeMap* getAttributes();

                    virtual jbool hasAttributes();

                    virtual JString* toString();

                    virtual void writeXml(JXmlWriteContext* context);

                    virtual void setIdAttributeName(JString* attName);

                    virtual JString* getIdAttributeName();

                    virtual void setUserObject(JObject* userObject);

                    virtual JObject* getUserObject();

                    virtual jshort getNodeType();

                    virtual JString* getTagName();

                    virtual jbool hasAttribute(JString* name);

                    virtual jbool hasAttributeNS(JString* namespaceURI, JString* localName);

                    virtual JString* getAttribute(JString* name);

                    virtual JString* getAttributeNS(JString* namespaceURI, JString* localName);

                    virtual JAttr* getAttributeNodeNS(JString* namespaceURI, JString* localName);

                    virtual void setAttribute(JString* name, JString* value);

                    virtual void setAttributeNS(JString* namespaceURI, JString* qualifiedName, JString* value);

                    virtual JAttr* setAttributeNodeNS(JAttr* newAttr);

                    virtual void removeAttribute(JString* name);

                    virtual void removeAttributeNS(JString* namespaceURI, JString* localName);

                    virtual JAttr* getAttributeNode(JString* name);

                    virtual JAttr* setAttributeNode(JAttr* newAttr);

                    virtual JAttr* removeAttributeNode(JAttr* oldAttr);

                    virtual JNode* cloneNode(jbool deep);

                    virtual void write(JWriter* out);

                    virtual JNodeList* getElementsByTagNameNS(JString* namespaceURI,JString* localName);

                    virtual JTypeInfo* getSchemaTypeInfo();

                    virtual void setIdAttribute(JString* name,jbool isId);

                    virtual void setIdAttributeNS(JString* namespaceURI,JString* localName,jbool isId);

                    virtual void setIdAttributeNode(JAttr* idAttr,jbool isId);

                    virtual JNodeList* getElementsByTagName(JString* name);

                    virtual ~JElementNode2();
                };
            }
        }
    }
}

#endif
