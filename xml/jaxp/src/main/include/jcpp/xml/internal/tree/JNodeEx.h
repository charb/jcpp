#ifndef JCPP_XML_INTERNAL_TREE_NODE_EX_H
#define JCPP_XML_INTERNAL_TREE_NODE_EX_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "org/w3c/dom/JNode.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{            

            	// @Class(canonicalName="javax.xml.internal.tree.NodeEx", simpleName="NodeEx");
                class JCPP_EXPORT JNodeEx : public virtual JNode, public virtual JXmlWritable{
                public:
                    static JClass* getClazz();

                    virtual JString* getInheritedAttribute(JString* name)=0;

                    virtual JString* getLanguage()=0;

                    virtual jint getIndexOf(JNode* maybeChild)=0;

                    virtual void setReadonly(jbool deep)=0;

                    virtual jbool isReadonly()=0;

                    virtual ~JNodeEx();
                };
            }
        }
    }
}

#endif
