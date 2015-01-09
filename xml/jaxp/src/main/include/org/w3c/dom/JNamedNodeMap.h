#ifndef ORG_W3C_DOM_NAMED_NODE_MAP_H
#define ORG_W3C_DOM_NAMED_NODE_MAP_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.NamedNodeMap", simpleName="NamedNodeMap");
            class JCPP_EXPORT JNamedNodeMap : public JInterface{
            public:
                static JClass* getClazz();

                virtual JNode* getNamedItem(JString* name)=0;

                virtual JNode* setNamedItem(JNode* arg)=0;

                virtual JNode* removeNamedItem(JString* name)=0;

                virtual JNode* item(jint index)=0;

                virtual jint getLength()=0;

                virtual JNode* getNamedItemNS(JString* namespaceURI,JString* localName)=0;

                virtual JNode* setNamedItemNS(JNode* arg)=0;

                virtual JNode* removeNamedItemNS(JString* namespaceURI,JString* localName)=0;

                virtual ~JNamedNodeMap();
            };
        }
    }
}

#endif
