#ifndef ORG_W3C_DOM_NAME_LIST_H
#define ORG_W3C_DOM_NAME_LIST_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.NameList", simpleName="NameList");
            class JCPP_EXPORT JNameList : public JInterface{
            public:
                static JClass* getClazz();

                virtual JString* getName(jint index)=0;

                virtual JString* getNamespaceURI(jint index)=0;

                virtual jint getLength()=0;

                virtual jbool contains(JString* str)=0;

                virtual jbool containsNS(JString* namespaceURI,JString* name)=0;

                virtual ~JNameList();
            };
        }
    }
}

#endif
