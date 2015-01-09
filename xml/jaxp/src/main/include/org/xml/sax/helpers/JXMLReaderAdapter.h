#ifndef ORG_XML_SAX_HELPERS_XML_READER_ADAPTER_H
#define ORG_XML_SAX_HELPERS_XML_READER_ADAPTER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "org/xml/sax/JXMLReader.h"
#include "org/xml/sax/JDocumentHandler.h"
#include "org/xml/sax/JParser.h"
#include "org/xml/sax/JAttributes.h"
#include "org/xml/sax/JAttributeList.h"
#include "org/xml/sax/JSAXParseException.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JDTDHandler.h"
#include "org/xml/sax/JContentHandler.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/helpers/JAttributesImpl.h"
#include "org/xml/sax/helpers/JNamespaceSupport.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

            	// @Class(canonicalName="org.xml.sax.helpers.XMLReaderAdapter", simpleName="XMLReaderAdapter");
                class JCPP_EXPORT JXMLReaderAdapter : public JObject, public JParser, public JContentHandler{
                protected:

                	// @Class(canonicalName="org.xml.sax.helpers.XMLReaderAdapter$AttributesAdapter", simpleName="XMLReaderAdapter$AttributesAdapter");
                    class JCPP_EXPORT JAttributesAdapter : public JObject, public JAttributeList{
                    protected:
                        JXMLReaderAdapter* adapter;
                        JAttributes* attributes;
                        JAttributesAdapter(JClass* _class,JXMLReaderAdapter* adapter);

                    public:
                        JAttributesAdapter(JXMLReaderAdapter* adapter);

                        static JClass* getClazz();

                        virtual void setAttributes(JAttributes* attributes);

                        virtual jint getLength();

                        virtual JString* getName(jint i);

                        virtual JString* getType(jint i);
                        
                        virtual JString* getValue(jint i);

                        virtual JString* getType(JString* qName);
                        
                        virtual JString* getValue(JString* qName);

                        virtual ~JAttributesAdapter();
                    };

                    
                    JXMLReader* xmlReader;
                    JDocumentHandler* documentHandler;
                    JAttributesAdapter* qAtts;
                    JXMLReaderAdapter(JClass* _class);
                    virtual void setup(JXMLReader* xmlReader);
                    virtual void setupXMLReader();
                    friend class JAttributesAdapter;

                public:
                    JXMLReaderAdapter();

                    JXMLReaderAdapter(JXMLReader* xmlReader);

                    static JClass* getClazz();

                    virtual void setEntityResolver(JEntityResolver* resolver);

                    virtual void setDTDHandler(JDTDHandler* handler);
                    
                    virtual void setDocumentHandler(JDocumentHandler* handler);

                    virtual void setErrorHandler(JErrorHandler* handler);

                    virtual void parse(JString* systemId);

                    virtual void parse(JInputSource* input);

                    virtual void setDocumentLocator(JLocator* locator);

                    virtual void startDocument();

                    virtual void endDocument();

                    virtual void startPrefixMapping(JString* prefix, JString* uri);

                    virtual void endPrefixMapping(JString* prefix);

                    virtual void startElement(JString* uri, JString* localName,JString* qName, JAttributes* atts);

                    virtual void endElement(JString* uri, JString* localName,JString* qName);

                    virtual void characters(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void processingInstruction(JString* target, JString* data);

                    virtual void skippedEntity(JString* name);

                    virtual ~JXMLReaderAdapter();
                };
            }
        }
    }
}

#endif
