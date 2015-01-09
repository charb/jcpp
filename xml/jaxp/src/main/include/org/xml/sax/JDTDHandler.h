#ifndef ORG_XML_SAX_DTD_HANDLER_H
#define ORG_XML_SAX_DTD_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JAttributes.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.DTDHandler", simpleName="DTDHandler");
            class JCPP_EXPORT JDTDHandler : public JInterface{
            public:
                static JClass* getClazz();

                virtual void notationDecl(JString* name,JString* publicId,JString* systemId)=0;

                virtual void unparsedEntityDecl(JString* name,JString* publicId,JString* systemId,JString* notationName)=0;

                virtual ~JDTDHandler();
            };
        }
    }
}

#endif
