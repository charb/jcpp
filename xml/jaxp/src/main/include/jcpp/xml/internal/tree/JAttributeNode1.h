#ifndef JCPP_XML_INTERNAL_TREE_ATTRIBUTE_NODE1_H
#define JCPP_XML_INTERNAL_TREE_ATTRIBUTE_NODE1_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/xml/internal/tree/JAttributeNode.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.AttributeNode1", simpleName="AttributeNode1");
                class JCPP_EXPORT JAttributeNode1 : public JAttributeNode{
                public:
                    JAttributeNode1(JString* qName,JString* value, jbool specified, JString* defaultValue);

                    static JClass* getClazz();

                    virtual JAttributeNode* makeClone();

                    virtual JString* getPrefix();

                    virtual JString* getLocalName();

                    virtual ~JAttributeNode1();
                };
            }
        }
    }
}

#endif
