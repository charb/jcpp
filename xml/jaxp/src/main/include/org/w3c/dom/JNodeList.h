#ifndef ORG_W3C_DOM_NODE_LIST_H
#define ORG_W3C_DOM_NODE_LIST_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.NodeList", simpleName="NodeList");
            class JCPP_EXPORT JNodeList : public JInterface{
            public:
                static JClass* getClazz();

                virtual JNode* item(jint index)=0;

                virtual jint getLength()=0;

                virtual ~JNodeList();
            };
        }
    }
}

#endif
