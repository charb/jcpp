#ifndef ORG_W3C_DOM_DOCUMENT_FRAGMENT_H
#define ORG_W3C_DOM_DOCUMENT_FRAGMENT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DocumentFragment", simpleName="DocumentFragment");
            class JCPP_EXPORT JDocumentFragment : public virtual JNode{
            public:
                static JClass* getClazz();

                virtual ~JDocumentFragment();
            };
        }
    }
}

#endif
