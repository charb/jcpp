#ifndef ORG_W3C_DOM_DOM_ERROR_HANDLER_H
#define ORG_W3C_DOM_DOM_ERROR_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JDOMError.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DOMErrorHandler", simpleName="DOMErrorHandler");
            class JCPP_EXPORT JDOMErrorHandler : public JInterface{
            public:
                static JClass* getClazz();

                virtual jbool handleError(JDOMError* error)=0;

                virtual ~JDOMErrorHandler();
            };
        }
    }
}

#endif
