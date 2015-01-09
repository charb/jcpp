#ifndef ORG_W3C_DOM_DOCUMENT_TYPE_H
#define ORG_W3C_DOM_DOCUMENT_TYPE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNamedNodeMap.h"

namespace org{
    namespace w3c{
        namespace dom{            

        	// @Class(canonicalName="org.w3c.dom.DocumentType", simpleName="DocumentType");
        	class JCPP_EXPORT JDocumentType : public virtual JNode{

            public:
                static JClass* getClazz();

                virtual JString* getName()=0;

                virtual JNamedNodeMap* getEntities()=0;

                virtual JNamedNodeMap* getNotations()=0;

                virtual JString* getPublicId()=0;

                virtual JString* getSystemId()=0;

                virtual JString* getInternalSubset()=0;

                virtual ~JDocumentType();
            };
        }
    }
}

#endif
