#ifndef ORG_W3C_DOM_ENTITY_REFERENCE_H
#define ORG_W3C_DOM_ENTITY_REFERENCE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.EntityReference", simpleName="EntityReference");
            class JCPP_EXPORT JEntityReference : public virtual JNode{
            public:
                static JClass* getClazz();

                virtual ~JEntityReference();
            };
        }
    }
}

#endif
