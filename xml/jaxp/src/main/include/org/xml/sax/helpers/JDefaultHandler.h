#ifndef ORG_XML_SAX_HELPERS_DEFAULT_HANDLER_H
#define ORG_XML_SAX_HELPERS_DEFAULT_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JDTDHandler.h"
#include "org/xml/sax/JContentHandler.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JSAXParseException.h"
#include "org/xml/sax/JAttributes.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

            	// @Class(canonicalName="org.xml.sax.helpers.DefaultHandler", simpleName="DefaultHandler");
                class JCPP_EXPORT JDefaultHandler : public JObject, public JEntityResolver, public JDTDHandler, public JContentHandler, public JErrorHandler{
                protected:
                    JDefaultHandler(JClass* _class);

                public:
                    JDefaultHandler();

                    static JClass* getClazz();

                    virtual JInputSource* resolveEntity(JString* publicId, JString* systemId);

                    virtual void notationDecl(JString* name, JString* publicId, JString* systemId);

                    virtual void unparsedEntityDecl(JString* name, JString* publicId,JString* systemId, JString* notationName);

                    virtual void setDocumentLocator(JLocator* locator);

                    virtual void startDocument();

                    virtual void endDocument();

                    virtual void startPrefixMapping(JString* prefix, JString* uri);
                    
                    virtual void endPrefixMapping(JString* prefix);

                    virtual void startElement(JString* uri, JString* localName,JString* qName, JAttributes* attributes);

                    virtual void endElement(JString* uri, JString* localName, JString* qName);

                    virtual void characters(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void processingInstruction(JString* target, JString* data);

                    virtual void skippedEntity(JString* name);

                    virtual void warning(JSAXParseException* e);

                    virtual void error(JSAXParseException* e);

                    virtual void fatalError(JSAXParseException* e);

                    virtual ~JDefaultHandler();
                };
            }
        }
    }
}

#endif
