#ifndef JCPP_XML_INTERNAL_TREE_NAMESPACED_NODE_H
#define JCPP_XML_INTERNAL_TREE_NAMESPACED_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JParentNode.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JNamedNodeMap.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.NamespacedNode", simpleName="NamespacedNode");
                class JCPP_EXPORT JNamespacedNode : public JParentNode{
                protected:
                    JString* qName;
                    JString* namespaceURI;
                    JNamespacedNode(JClass* _class,JString* namespaceURI,JString* qName);

                public:
                    static JClass* getClazz();

                    virtual JString* getNamespaceURI();

                    virtual JString* getPrefix();

                    virtual void setPrefix(JString* prefix);

                    virtual JString* getLocalName();

                    virtual JString* getNodeName();

                    virtual ~JNamespacedNode();
                };
            }
        }
    }
}

#endif
