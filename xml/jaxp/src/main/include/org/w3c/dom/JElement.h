#ifndef ORG_W3C_DOM_ELEMENT_H
#define ORG_W3C_DOM_ELEMENT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JAttr.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JTypeInfo.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.Element", simpleName="Element");
            class JCPP_EXPORT JElement : public virtual JNode{
            public:
                static JClass* getClazz();

                virtual JString* getTagName()=0;

                virtual JString* getAttribute(JString* name)=0;

                virtual void setAttribute(JString* name,JString* value)=0;

                virtual void removeAttribute(JString* name)=0;

                virtual JAttr* getAttributeNode(JString* name)=0;

                virtual JAttr* setAttributeNode(JAttr* newAttr)=0;
    
                virtual JAttr* removeAttributeNode(JAttr* oldAttr)=0;

                virtual JNodeList* getElementsByTagName(JString* name)=0;

                virtual JString* getAttributeNS(JString* namespaceURI,JString* localName)=0;

                virtual void setAttributeNS(JString* namespaceURI,JString* qualifiedName,JString* value)=0;

                virtual void removeAttributeNS(JString* namespaceURI,JString* localName)=0;

                virtual JAttr* getAttributeNodeNS(JString* namespaceURI,JString* localName)=0;

                virtual JAttr* setAttributeNodeNS(JAttr* newAttr)=0;

                virtual JNodeList* getElementsByTagNameNS(JString* namespaceURI,JString* localName)=0;

                virtual jbool hasAttribute(JString* name)=0;

                virtual jbool hasAttributeNS(JString* namespaceURI,JString* localName)=0;

                virtual JTypeInfo* getSchemaTypeInfo()=0;

                virtual void setIdAttribute(JString* name,jbool isId)=0;

                virtual void setIdAttributeNS(JString* namespaceURI,JString* localName,jbool isId)=0;

                virtual void setIdAttributeNode(JAttr* idAttr,jbool isId)=0;

                virtual ~JElement();
            };
        }
    }
}

#endif
