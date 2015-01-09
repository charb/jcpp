#ifndef ORG_W3C_DOM_DOM_CONFIGURATION_H
#define ORG_W3C_DOM_DOM_CONFIGURATION_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JDOMStringList.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DOMConfiguration", simpleName="DOMConfiguration");
            class JCPP_EXPORT JDOMConfiguration : public JInterface{
            public:
                static JClass* getClazz();

                virtual void setParameter(JString* name,JObject* value)=0;
                
                virtual JObject* getParameter(JString* name)=0;

                virtual jbool canSetParameter(JString* name,JObject* value)=0;

                virtual JDOMStringList* getParameterNames()=0;

                virtual ~JDOMConfiguration();
            };
        }
    }
}

#endif
