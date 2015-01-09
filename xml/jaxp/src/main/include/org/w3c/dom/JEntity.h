#ifndef ORG_W3C_DOM_ENTITY_H
#define ORG_W3C_DOM_ENTITY_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.Entity", simpleName="Entity");
            class JCPP_EXPORT JEntity : public virtual JNode{
            public:
                static JClass* getClazz();

                virtual JString* getPublicId()=0;

                virtual JString* getSystemId()=0;

                virtual JString* getNotationName()=0;

                virtual JString* getInputEncoding()=0;

                virtual JString* getXmlEncoding()=0;

                virtual JString* getXmlVersion()=0;

                virtual ~JEntity();
            };
        }
    }
}

#endif
