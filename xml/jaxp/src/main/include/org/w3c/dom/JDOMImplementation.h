#ifndef ORG_W3C_DOM_DOM_IMPLEMENTATION_H
#define ORG_W3C_DOM_DOM_IMPLEMENTATION_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JDocumentType.h"
#include "org/w3c/dom/JDocument.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DOMImplementation", simpleName="DOMImplementation");
            class JCPP_EXPORT JDOMImplementation : public JInterface{
            public:
                static JClass* getClazz();

                virtual jbool hasFeature(JString* feature,JString* version)=0;

                virtual JDocumentType* createDocumentType(JString* qualifiedName,JString* publicId,JString* systemId)=0;
                
                virtual JDocument* createDocument(JString* namespaceURI,JString* qualifiedName,JDocumentType* doctype)=0;

                virtual JObject* getFeature(JString* feature,JString* version)=0;

                virtual ~JDOMImplementation();
            };
        }
    }
}

#endif
