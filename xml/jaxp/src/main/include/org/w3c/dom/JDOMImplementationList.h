#ifndef ORG_W3C_DOM_DOM_IMPLEMENTATION_LIST_H
#define ORG_W3C_DOM_DOM_IMPLEMENTATION_LIST_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JDOMImplementation.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DOMImplementationList", simpleName="DOMImplementationList");
            class JCPP_EXPORT JDOMImplementationList : public JInterface{
            public:
                static JClass* getClazz();

                virtual JDOMImplementation* item(jint index)=0;

                virtual jint getLength()=0;

                virtual ~JDOMImplementationList();
            };
        }
    }
}

#endif
