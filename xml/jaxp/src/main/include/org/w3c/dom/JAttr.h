#ifndef ORG_W3C_DOM_ATTR_H
#define ORG_W3C_DOM_ATTR_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JTypeInfo.h"

namespace org{
    namespace w3c{
        namespace dom{
            class JElement;
            class JTypeInfo;
            
            // @Class(canonicalName="org.w3c.dom.Attr", simpleName="Attr");
            class JCPP_EXPORT JAttr : public virtual JNode{
            public:
                static JClass* getClazz();

                virtual JString* getName()=0;

                virtual jbool getSpecified()=0;

                virtual JString* getValue()=0;
                
                virtual void setValue(JString* value)=0;
                
                virtual JElement* getOwnerElement()=0;

                virtual JTypeInfo* getSchemaTypeInfo()=0;

                virtual jbool isId()=0;

                virtual ~JAttr();
            };
        }
    }
}

#endif
