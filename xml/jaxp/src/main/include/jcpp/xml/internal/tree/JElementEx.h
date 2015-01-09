#ifndef JCPP_XML_INTERNAL_TREE_ELEMENT_EX_H
#define JCPP_XML_INTERNAL_TREE_ELEMENT_EX_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JNodeEx.h"
#include "org/w3c/dom/JElement.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{            

            	// @Class(canonicalName="javax.xml.internal.tree.ElementEx", simpleName="ElementEx");
            	class JCPP_EXPORT JElementEx : public virtual JElement, public virtual JNodeEx{
                public:
                    static JClass* getClazz();

                    virtual JString* getIdAttributeName()=0;

                    virtual JObject* getUserObject()=0;

                    virtual void setUserObject(JObject* obj)=0;

                    virtual void trimToSize()=0;

                    virtual ~JElementEx();
                };
            }
        }
    }
}

#endif
