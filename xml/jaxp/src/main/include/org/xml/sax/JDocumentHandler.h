#ifndef ORG_XML_SAX_DOCUMENT_HANDLER_H
#define ORG_XML_SAX_DOCUMENT_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JAttributes.h"
#include "org/xml/sax/JAttributeList.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.DocumentHandler", simpleName="DocumentHandler");
            class JCPP_EXPORT JDocumentHandler : public JInterface{
            public:
                static JClass* getClazz();

                virtual void setDocumentLocator(JLocator* locator)=0;

                virtual void startDocument()=0;

                virtual void endDocument()=0;
                
                virtual void startElement(JString* name, JAttributeList* atts)=0;

                virtual void endElement(JString* name)=0;

                virtual void characters(JPrimitiveCharArray* ch, jint start, jint length)=0;

                virtual void ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length)=0;

                virtual void processingInstruction(JString* target, JString* data)=0;

                virtual ~JDocumentHandler();
            };
        }
    }
}

#endif
