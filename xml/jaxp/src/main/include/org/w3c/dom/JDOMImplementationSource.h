#ifndef ORG_W3C_DOM_DOM_IMPLEMENTATION_SOURCE_H
#define ORG_W3C_DOM_DOM_IMPLEMENTATION_SOURCE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JDOMImplementation.h"
#include "org/w3c/dom/JDOMImplementationList.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DOMImplementationSource", simpleName="DOMImplementationSource");
            class JCPP_EXPORT JDOMImplementationSource : public JInterface{
            public:
                static JClass* getClazz();

                virtual JDOMImplementation* getDOMImplementation(JString* features)=0;

                virtual JDOMImplementationList* getDOMImplementationList(JString* features)=0;

                virtual ~JDOMImplementationSource();
            };
        }
    }
}

#endif
