#ifndef ORG_W3C_DOM_HANDLER_BASE_H
#define ORG_W3C_DOM_HANDLER_BASE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JDTDHandler.h"
#include "org/xml/sax/JDocumentHandler.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/JAttributeList.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JSAXParseException.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.HandlerBase", simpleName="HandlerBase");
            class JCPP_EXPORT JHandlerBase : public JObject, public JEntityResolver, public JDTDHandler, public JDocumentHandler, public JErrorHandler{
            protected:
            	JHandlerBase(JClass* _class);

            public:
                JHandlerBase();

                static JClass* getClazz();

                virtual JInputSource* resolveEntity(JString* publicId, JString* systemId);

                virtual void notationDecl(JString* name, JString* publicId, JString* systemId);

				virtual void unparsedEntityDecl(JString* name, JString* publicId,JString* systemId, JString* notationName);

				virtual void setDocumentLocator(JLocator* locator);

				virtual void startDocument();

				virtual void endDocument();

				virtual void startElement(JString* name, JAttributeList* attributes);

				virtual void endElement(JString* name);

				virtual void characters(JPrimitiveCharArray* ch, jint start, jint length);

				virtual void ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length);

				virtual void processingInstruction(JString* target, JString* data);

				virtual void warning(JSAXParseException* e);

				virtual void error(JSAXParseException* e);

				virtual void fatalError(JSAXParseException* e);

                virtual ~JHandlerBase();
            };
        }
    }
}

#endif
