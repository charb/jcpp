#ifndef ORG_XML_SAX_HELPERS_PARSER_ADAPTER_H
#define ORG_XML_SAX_HELPERS_PARSER_ADAPTER_H

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

            	// @Class(canonicalName="org.xml.sax.helpers.ParserAdapter", simpleName="ParserAdapter");
                class JCPP_EXPORT JParserAdapter : public JObject, public JXMLReader, public JDocumentHandler{
                protected:

                	// @Class(canonicalName="org.xml.sax.helpers.ParserAdapter$AttributeListAdapter", simpleName="ParserAdapter$AttributeListAdapter");
                    class JCPP_EXPORT JAttributeListAdapter : public JObject, public JAttributes{
                    protected:
                        JParserAdapter* adapter;
                        JAttributeList* qAtts;
                        JAttributeListAdapter(JClass* _class,JParserAdapter* adapter);

                    public:
                        JAttributeListAdapter(JParserAdapter* adapter);

                        static JClass* getClazz();

                        virtual void setAttributeList(JAttributeList* qAtts);

                        virtual jint getLength();
                        
                        virtual JString* getURI(jint i);

                        virtual JString* getLocalName(jint i);

                        virtual JString* getQName(jint i);

                        virtual JString* getType(jint i);

                        virtual JString* getValue(jint i);

                        virtual jint getIndex(JString* uri, JString* localName);

                        virtual jint getIndex(JString* qName);

                        virtual JString* getType(JString* uri, JString* localName);

                        virtual JString* getType(JString* qName);

                        virtual JString* getValue(JString* uri, JString* localName);

                        virtual JString* getValue(JString* qName);

                        virtual ~JAttributeListAdapter();
                    };

                    static JString* FEATURES;
                    static JString* NAMESPACES;
                    static JString* NAMESPACE_PREFIXES;
                    static JString* XMLNS_URIs;

                    JNamespaceSupport* nsSupport;
                    JAttributeListAdapter* attAdapter;
                    jbool parsing;
                    JPrimitiveObjectArray* nameParts;
                    JParser* parser;
                    JAttributesImpl* atts;
                    jbool namespaces;
                    jbool prefixes;
                    jbool uris;
                    JLocator* locator;
                    JEntityResolver* entityResolver;
                    JDTDHandler* dtdHandler;
                    JContentHandler* contentHandler;
                    JErrorHandler* errorHandler;

                    JParserAdapter(JClass* _class);
                    virtual void setup(JParser* parser);
                    virtual void reportError(JString* message);
                    virtual JSAXParseException* makeException(JString* message);
                    virtual void checkNotParsing(JString* type, JString* name);
                    virtual void setupParser();
                    friend class JAttributeListAdapter;

                public:
                    JParserAdapter();

                    JParserAdapter(JParser* parser);

                    static JClass* getClazz();

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

                    virtual void parse(JString* systemId);

                    virtual void parse(JInputSource* input);

                    virtual void setDocumentLocator(JLocator* locator);

                    virtual void startDocument();

                    virtual void endDocument();

                    virtual void startElement(JString* qName, JAttributeList* qAtts);

                    virtual void endElement(JString* qName);

                    virtual void characters(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void ignorableWhitespace(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void processingInstruction(JString* target, JString* data);

                    virtual JPrimitiveObjectArray* processName(JString* qName, jbool isAttribute,jbool useException);

                    virtual ~JParserAdapter();
                };
            }
        }
    }
}

#endif
