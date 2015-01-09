#ifndef JCPP_XML_INTERNAL_TREE_COMMENT_NODE_H
#define JCPP_XML_INTERNAL_TREE_COMMENT_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/xml/internal/tree/JDataNode.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JComment.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.CommentNode", simpleName="CommentNode");
                class JCPP_EXPORT JCommentNode : public JDataNode, public virtual JComment{
                public:
                    JCommentNode();

                    JCommentNode(JString* data);

                    JCommentNode(JPrimitiveCharArray* buf, jint offset, jint len);

                    static JClass* getClazz();

                    virtual jshort getNodeType();

                    virtual void writeXml(JXmlWriteContext* context);

                    virtual JNode* cloneNode(jbool deep);

                    virtual JString* getNodeName();

                    virtual ~JCommentNode();
                };
            }
        }
    }
}

#endif
