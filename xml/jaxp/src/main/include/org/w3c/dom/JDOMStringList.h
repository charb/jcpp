#ifndef ORG_W3C_DOM_DOM_STRING_LIST_H
#define ORG_W3C_DOM_DOM_STRING_LIST_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.DOMStringList", simpleName="DOMStringList");
            class JCPP_EXPORT JDOMStringList : public JInterface{
            public:
                static JClass* getClazz();

                virtual JString* item(jint index)=0;

                virtual jint getLength()=0;

                virtual jbool contains(JString* str)=0;

                virtual ~JDOMStringList();
            };
        }
    }
}

#endif
