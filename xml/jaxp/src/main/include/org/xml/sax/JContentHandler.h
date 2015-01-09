#ifndef ORG_XML_SAX_CONTENT_HANDLER_H
#define ORG_XML_SAX_CONTENT_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JAttributes.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.ContentHandler", simpleName="ContentHandler");
            class JCPP_EXPORT JContentHandler : public JInterface{
            public:
                static JClass* getClazz();

                virtual void setDocumentLocator(JLocator* locator)=0;

                virtual void startDocument()=0;
                
                virtual void endDocument()=0;

                virtual void startPrefixMapping(JString* prefix, JString* uri)=0;

                virtual void endPrefixMapping(JString* prefix)=0;

                virtual void startElement(JString* uri, JString* localName,JString* qName, JAttributes* atts)=0;

                virtual void endElement(JString* uri, JString* localName,JString* qName)=0;

                virtual void characters(JPrimitiveCharArray* ch, jint start, jint length)=0;
                
                virtual void ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length)=0;

                virtual void processingInstruction(JString* target, JString* data)=0;

                virtual void skippedEntity(JString* name)=0;

                virtual ~JContentHandler();
            };
        }
    }
}

#endif
