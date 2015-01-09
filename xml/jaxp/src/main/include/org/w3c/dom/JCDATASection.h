#ifndef ORG_W3C_DOM_CDATASECTION_H
#define ORG_W3C_DOM_CDATASECTION_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JText.h"

namespace org{
    namespace w3c{
        namespace dom{            

        	// @Class(canonicalName="org.w3c.dom.CDATASection", simpleName="CDATASection");
        	class JCPP_EXPORT JCDATASection : public virtual JText{
            public:
                static JClass* getClazz();

                virtual ~JCDATASection();
            };
        }
    }
}

#endif
