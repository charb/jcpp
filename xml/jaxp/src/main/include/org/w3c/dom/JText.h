#ifndef ORG_W3C_DOM_TEXT_H
#define ORG_W3C_DOM_TEXT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JCharacterData.h"

namespace org{
    namespace w3c{
        namespace dom{            

        	// @Class(canonicalName="org.w3c.dom.Text", simpleName="Text");
        	class JCPP_EXPORT JText : public virtual JCharacterData{
            public:
                static JClass* getClazz();

                virtual JText* splitText(jint offset)=0;

				virtual jbool isElementContentWhitespace()=0;

				virtual JString* getWholeText()=0;

				virtual JText* replaceWholeText(JString* content)=0;

                virtual ~JText();
            };
        }
    }
}

#endif
