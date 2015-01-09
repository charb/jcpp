#ifndef ORG_XML_SAX_HELPERS_XML_FILTER_IMPL_H
#define ORG_XML_SAX_HELPERS_XML_FILTER_IMPL_H

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
#include "org/xml/sax/JXMLReader.h"
#include "org/xml/sax/JXMLFilter.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

            	// @Class(canonicalName="org.xml.sax.helpers.XMLFilterImpl", simpleName="XMLFilterImpl");
                class JCPP_EXPORT JXMLFilterImpl : public JObject, public JXMLFilter, public JEntityResolver, public JDTDHandler, public JContentHandler, public JErrorHandler{
                protected:
                    JXMLReader* parent;
                    JLocator* locator;
                    JEntityResolver* entityResolver;
                    JDTDHandler* dtdHandler;
                    JContentHandler* contentHandler;
                    JErrorHandler* errorHandler;
                    JXMLFilterImpl(JClass* _class);
                    virtual void setupParse();

                public:
                    JXMLFilterImpl();

                    JXMLFilterImpl(JXMLReader* parent);

                    static JClass* getClazz();

                    virtual void setParent(JXMLReader* parent);
                    
                    virtual JXMLReader* getParent();

                    virtual void setFeature(JString* name, jbool value);

                    virtual jbool getFeature(JString* name);

                    virtual void setProperty(JString* name, JObject* value);

                    virtual JObject* getProperty(JString* name);

                    virtual void setEntityResolver(JEntityResolver* resolver);

                    virtual JEntityResolver* getEntityResolver();

                    virtual void setDTDHandler(JDTDHandler* handler);

                    virtual JDTDHandler* getDTDHandler();

                    virtual void setContentHandler(JContentHandler* handler);

                    virtual JContentHandler* getContentHandler();

                    virtual void setErrorHandler(JErrorHandler* handler);

                    virtual JErrorHandler* getErrorHandler();

                    virtual void parse(JInputSource* input);

                    virtual void parse(JString* systemId);

                    virtual JInputSource* resolveEntity(JString* publicId, JString* systemId);

                    virtual void notationDecl(JString* name, JString* publicId, JString* systemId);

                    virtual void unparsedEntityDecl(JString* name, JString* publicId,JString* systemId, JString* notationName);

                    virtual void setDocumentLocator(JLocator* locator);

                    virtual void startDocument();

                    virtual void endDocument();

                    virtual void startPrefixMapping(JString* prefix, JString* uri);

                    virtual void endPrefixMapping(JString* prefix);

                    virtual void startElement(JString* uri, JString* localName, JString* qName,JAttributes* atts);

                    virtual void endElement(JString* uri, JString* localName, JString* qName);

                    virtual void characters(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void processingInstruction(JString* target, JString* data);

                    virtual void skippedEntity(JString* name);

                    virtual void warning(JSAXParseException* e);

                    virtual void error(JSAXParseException* e);

                    virtual void fatalError(JSAXParseException* e);

                    virtual ~JXMLFilterImpl();
                };
            }
        }
    }
}

#endif
