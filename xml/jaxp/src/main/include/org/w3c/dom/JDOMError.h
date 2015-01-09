#ifndef ORG_W3C_DOM_DOM_ERROR_H
#define ORG_W3C_DOM_DOM_ERROR_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JDOMLocator.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DOMError", simpleName="DOMError");
            class JCPP_EXPORT JDOMError : public JInterface{
            public:
                static JClass* getClazz();

                static jshort SEVERITY_WARNING;
                static jshort SEVERITY_ERROR;
                static jshort SEVERITY_FATAL_ERROR;

                virtual jshort getSeverity()=0;

                virtual JString* getMessage()=0;

                virtual JString* getType()=0;

                virtual JObject* getRelatedException()=0;
                
                virtual JObject* getRelatedData()=0;

                virtual JDOMLocator* getLocation()=0;

                virtual ~JDOMError();
            };
        }
    }
}

#endif
