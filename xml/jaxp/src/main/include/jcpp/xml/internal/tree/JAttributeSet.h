#ifndef JCPP_XML_INTERNAL_TREE_ATTRIBUTE_SET_H
#define JCPP_XML_INTERNAL_TREE_ATTRIBUTE_SET_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JVector.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JNamedNodeMap.h"
#include "org/xml/sax/JAttributes.h"

using namespace org::w3c::dom;
using namespace org::xml::sax;
using namespace jcpp::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.AttributeSet", simpleName="AttributeSet");
                class JCPP_EXPORT JAttributeSet : public JObject, public JNamedNodeMap, public JXmlWritable{
                protected:
                    jbool readonly;
                    JVector* list;
                    JElement* ownerElement;

                public:
                    JAttributeSet();

                    JAttributeSet(JElement* ownerElement);

                    JAttributeSet(JAttributeSet* original, jbool deep);

                    JAttributeSet(JAttributeSet* original);

                    static JClass* getClazz();

                    static JAttributeSet* createAttributeSet2(JAttributes* source);

                    static JAttributeSet* createAttributeSet1(JAttributes* source);

                    virtual void trimToSize();

                    virtual void setReadonly();

                    virtual jbool isReadonly();

                    virtual void setOwnerElement(JElement* e);

                    virtual JString* getValue(JString* name);

                    virtual JNode* getNamedItem(JString* name);

                    virtual JNode* getNamedItemNS(JString* namespaceURI, JString* localName);

                    virtual jint getLength();

                    virtual JNode* item(jint index);

                    virtual JNode* removeNamedItem(JString* name);

                    virtual JNode* removeNamedItemNS(JString* namespaceURI, JString* localName);

                    virtual JNode* setNamedItem(JNode* value);

                    virtual JNode* setNamedItemNS(JNode* arg);

                    virtual void writeXml(JXmlWriteContext* context);

                    virtual void writeChildrenXml(JXmlWriteContext* context);

                    virtual JString* toString();

                    virtual ~JAttributeSet();
                };
            }
        }
    }
}

#endif
