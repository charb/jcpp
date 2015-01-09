#ifndef JCPP_XML_INTERNAL_TREE_XML_DOCUMENT_BUILDER_H
#define JCPP_XML_INTERNAL_TREE_XML_DOCUMENT_BUILDER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "jcpp/xml/internal/tree/JNodeEx.h"
#include "jcpp/xml/internal/tree/JDoctype.h"
#include "jcpp/xml/internal/tree/JElementFactory.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JNamedNodeMap.h"
#include "org/xml/sax/JContentHandler.h"
#include "org/xml/sax/JDTDHandler.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/ext/JLexicalHandler.h"
#include "org/xml/sax/ext/JDeclHandler.h"

using namespace org::w3c::dom;
using namespace org::xml::sax;
using namespace org::xml::sax::ext;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.XmlDocumentBuilder", simpleName="XmlDocumentBuilder");
                class JCPP_EXPORT JXmlDocumentBuilder : public JObject, public virtual JContentHandler, public virtual JLexicalHandler, public virtual JDeclHandler, public virtual JDTDHandler{
                protected:
                    JXmlDocument* document;
                    JLocator* locator;
                    JElementFactory*  factory;
                    JVector* attrTmp;
                    JPrimitiveObjectArray* elementStack;
                    jint topOfStack;
                    jbool inDTD;
                    jbool inCDataSection;
                    JDoctype* doctype;
                    jbool disableNamespaces;    
                    jbool ignoreWhitespace;
                    jbool expandEntityRefs;
                    jbool ignoreComments;
                    jbool putCDATAIntoText;
                    JXmlDocumentBuilder(JClass* _class);

                public:
                    JXmlDocumentBuilder();

                    static JClass* getClazz();

                    virtual jbool isIgnoringLexicalInfo();

                    virtual void setIgnoringLexicalInfo(jbool value);

                    virtual void setIgnoreWhitespace(jbool value);

                    virtual void setExpandEntityReferences(jbool value);

                    virtual void setIgnoreComments(jbool value);

                    virtual void setPutCDATAIntoText(jbool value);

                    virtual jbool getDisableNamespaces();

                    virtual void setDisableNamespaces(jbool value);

                    virtual JXmlDocument* getDocument();

                    virtual void setDocumentLocator(JLocator* locator);

                    virtual JXmlDocument* createDocument();

                    virtual void setElementFactory(JElementFactory* factory);

                    virtual JElementFactory* getElementFactory();

                    virtual void startDocument();

                    virtual void endDocument();

                    virtual void startPrefixMapping(JString* prefix, JString* uri);

                    virtual void endPrefixMapping(JString* prefix);

                    virtual void startElement(JString* namespaceURI, JString* localName,JString* qName, JAttributes* attributes);

                    virtual void endElement(JString* namespaceURI, JString* localName,JString* qName);

                    virtual void characters(JPrimitiveCharArray* buf, jint offset, jint len);

                    virtual void ignorableWhitespace(JPrimitiveCharArray* buf , jint offset, jint len);

                    virtual void processingInstruction(JString* name, JString* instruction);

                    virtual void skippedEntity(JString* name);

                    virtual void startDTD(JString* name, JString* publicId, JString* systemId);

                    virtual void endDTD();

                    virtual void startEntity(JString* name);

                    virtual void endEntity(JString* name);

                    virtual void startCDATA();

                    virtual void endCDATA();

                    virtual void comment(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void elementDecl(JString* name, JString* model);

                    virtual void attributeDecl(JString* eName, JString* aName, JString* type,JString* valueDefault, JString* value);

                    virtual void internalEntityDecl(JString* name, JString* value);

                    virtual void externalEntityDecl(JString* name, JString* publicId,JString* systemId);

                    virtual void notationDecl(JString* n, JString* p, JString* s);

                    virtual void unparsedEntityDecl(JString* name, JString* publicId, JString* systemId, JString* notation);

                    virtual ~JXmlDocumentBuilder();
                };
            }
        }
    }
}

#endif
