#ifndef JCPP_XML_INTERNAL_TREE_TEXT_NODE_H
#define JCPP_XML_INTERNAL_TREE_TEXT_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "jcpp/xml/internal/tree/JDataNode.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JText.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.TextNode", simpleName="TextNode");
                class JCPP_EXPORT JTextNode : public JDataNode, public virtual JText{
                protected:
                    JTextNode(JClass* _class);
                    JTextNode(JClass* _class,JPrimitiveCharArray* buf, jint offset, jint len);
                    JTextNode(JClass* _class,JString* s);

                public:
                    JTextNode();

                    JTextNode(JPrimitiveCharArray* buf, jint offset, jint len);

                    JTextNode(JString* s);

                    static JClass* getClazz();

                    virtual void writeXml(JXmlWriteContext* context);

                    virtual void joinNextText();

                    virtual jshort getNodeType();

                    virtual JText* splitText(jint offset);

                    virtual JNode* cloneNode(jbool deep);

                    virtual JString* getNodeName();

                    virtual jbool isElementContentWhitespace();

                    virtual JString* getWholeText();

                    virtual JText* replaceWholeText(JString* content);

                    virtual ~JTextNode();
                };
            }
        }
    }
}

#endif
