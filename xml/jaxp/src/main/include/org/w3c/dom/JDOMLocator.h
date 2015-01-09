#ifndef ORG_W3C_DOM_DOM_LOCATOR_H
#define ORG_W3C_DOM_DOM_LOCATOR_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DOMLocator", simpleName="DOMLocator");
            class JCPP_EXPORT JDOMLocator : public JInterface{
            public:
                static JClass* getClazz();

                virtual jint getLineNumber()=0;

                virtual jint getColumnNumber()=0;

                virtual jint getByteOffset()=0;

                virtual jint getUtf16Offset()=0;

                virtual JNode* getRelatedNode()=0;

                virtual JString* getUri()=0;

                virtual ~JDOMLocator();
            };
        }
    }
}

#endif
