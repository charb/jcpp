#ifndef JCPP_XML_INTERNAL_TREE_CDATA_NODE_H
#define JCPP_XML_INTERNAL_TREE_CDATA_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "jcpp/xml/internal/tree/JTextNode.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JCDATASection.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.CDataNode", simpleName="CDataNode");
                class JCPP_EXPORT JCDataNode : public JTextNode, public virtual JCDATASection{
                public:
                    JCDataNode();

                    JCDataNode(JPrimitiveCharArray* buf, jint offset, jint len);

                    JCDataNode(JString* s);

                    static JClass* getClazz();

                    virtual void writeXml(JXmlWriteContext* context);

                    virtual jshort getNodeType();

                    virtual JNode* cloneNode(jbool deep);

                    virtual JString* getNodeName();

                    virtual ~JCDataNode();
                };
            }
        }
    }
}

#endif
