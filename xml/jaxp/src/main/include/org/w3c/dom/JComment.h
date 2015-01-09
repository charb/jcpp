#ifndef ORG_W3C_DOM_COMMENT_H
#define ORG_W3C_DOM_COMMENT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JCharacterData.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.Comment", simpleName="Comment");
            class JCPP_EXPORT JComment : public virtual JCharacterData{
            public:
                static JClass* getClazz();

                virtual ~JComment();
            };
        }
    }
}

#endif
