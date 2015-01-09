#ifndef ORG_W3C_DOM_NOTATION_H
#define ORG_W3C_DOM_NOTATION_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.Notation", simpleName="Notation");
            class JCPP_EXPORT JNotation : public virtual JNode{
            public:
                static JClass* getClazz();

                virtual JString* getPublicId()=0;

                virtual JString* getSystemId()=0;

                virtual ~JNotation();
            };
        }
    }
}

#endif
