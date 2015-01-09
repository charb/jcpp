#ifndef JCPP_XML_INTERNAL_TREE_PI_NODE_H
#define JCPP_XML_INTERNAL_TREE_PI_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "jcpp/xml/internal/tree/JNodeBase.h"
#include "jcpp/xml/internal/tree/JTreeWalker.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JProcessingInstruction.h"
#include "org/w3c/dom/JNamedNodeMap.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.PINode", simpleName="PINode");
                class JCPP_EXPORT JPINode : public JNodeBase, public JProcessingInstruction{
                protected:
                    JString* target;
                    JPrimitiveCharArray* data;

                public:
                    JPINode();

                    JPINode(JString* target,JString* text);   
                    
                    JPINode(JString* target, JPrimitiveCharArray* buf, jint offset, jint len);

                    static JClass* getClazz();

                    virtual jshort getNodeType();

                    virtual JString* getTarget();

                    virtual void setTarget(JString* target);

                    virtual JString* getData();

                    virtual void setData(JString* data);

                    virtual JString* getNodeValue();

                    virtual void setNodeValue(JString* data);

                    virtual void writeXml(JXmlWriteContext* context);

                    virtual JNode* cloneNode(jbool deep);

                    virtual JString* getNodeName();

                    virtual ~JPINode();
                };
            }
        }
    }
}

#endif
