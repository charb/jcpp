#ifndef JCPP_XML_INTERNAL_TREE_ELEMENT_NODE_H
#define JCPP_XML_INTERNAL_TREE_ELEMENT_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JElementNode2.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JNamedNodeMap.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.ElementNode", simpleName="ElementNode");
                class JCPP_EXPORT JElementNode : public JElementNode2{
                public:
                    JElementNode();

                    JElementNode(JString* name);

                    static JClass* getClazz();

                    virtual JElementNode2* makeClone();

                    virtual void setTag(JString* t);

                    virtual JString* getPrefix();

                    virtual JString* getLocalName();

                    virtual ~JElementNode();
                };
            }
        }
    }
}

#endif
