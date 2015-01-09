#ifndef ORG_W3C_DOM_PROCESSING_INSTRUCTION_H
#define ORG_W3C_DOM_PROCESSING_INSTRUCTION_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.ProcessingInstruction", simpleName="ProcessingInstruction");
            class JCPP_EXPORT JProcessingInstruction : public virtual JNode{
            public:
                static JClass* getClazz();

                virtual JString* getTarget()=0;

                virtual JString* getData()=0;
                
                virtual void setData(JString* data)=0;

                virtual ~JProcessingInstruction();
            };
        }
    }
}

#endif
