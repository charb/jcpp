#ifndef JCPP_XML_INTERNAL_TREE_XML_DOCUMENT_H
#define JCPP_XML_INTERNAL_TREE_XML_DOCUMENT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JOutputStream.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/xml/internal/tree/JParentNode.h"
#include "jcpp/xml/internal/tree/JDocumentEx.h"
#include "jcpp/xml/internal/tree/JTextNode.h"
#include "jcpp/xml/internal/tree/JElementEx.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JNamedNodeMap.h"
#include "org/xml/sax/JInputSource.h"

using namespace org::w3c::dom;
using namespace org::xml::sax;
using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.XmlDocument", simpleName="XmlDocument");
                class JCPP_EXPORT JXmlDocument : public JParentNode, public virtual JDocumentEx{
                protected:

                	// @Class(canonicalName="javax.xml.internal.tree.XmlDocument$DocFragNode", simpleName="XmlDocument$DocFragNode");
                    class JDocFragNode : public JParentNode, public JDocumentFragment{
                    public:
                        JDocFragNode();

                        static JClass* getClazz();

                        virtual void checkChildType(jint type);

                        virtual void writeXml(JXmlWriteContext* context);

                        virtual JNode* getParentNode();

                        virtual void setParentNode(JNode* p);

                        virtual jshort getNodeType();

                        virtual JString* getNodeName();

                        virtual JNode* cloneNode(jbool deep);

                        virtual ~JDocFragNode();
                    };

                    // @Class(canonicalName="javax.xml.internal.tree.XmlDocument$EntityRefNode", simpleName="XmlDocument$EntityRefNode");
                    class JEntityRefNode : public JParentNode, public JEntityReference{
                    protected:
                        JString*  entity;

                    public:
                        JEntityRefNode(JString* name);

                        static JClass* getClazz();
                        
                        virtual void checkChildType(jint type);

                        virtual void writeXml(JXmlWriteContext* context);

                        virtual jshort getNodeType();

                        virtual JString* getNodeName();

                        virtual JNode* cloneNode(jbool deep);

                        virtual ~JEntityRefNode();
                    };

                    // @Class(canonicalName="javax.xml.internal.tree.XmlDocument$ExtWriteContext", simpleName="XmlDocument$ExtWriteContext");
                    class JExtWriteContext : public JXmlWriteContext{
                    protected:
                        JXmlDocument* xmlDocument;

                    public:
                        JExtWriteContext(JXmlDocument* xmlDocument,JWriter* out);
                        
                        JExtWriteContext(JXmlDocument* xmlDocument,JWriter* out, jint level);

                        static JClass* getClazz();

                        virtual jbool isEntityDeclared(JString* name);

                        virtual ~JExtWriteContext();
                    };

                    JString* systemId;
                    JElementFactory* factory;
                    jint  mutationCount;
                    jbool replaceRootElement;
                    JXmlDocument(JClass* _class);
                    friend class JParentNode;

                public:
                    JXmlDocument();

                    static JClass* getClazz();

                    static JXmlDocument* createXmlDocument(JString* documentURI,jbool doValidate);

                    static JXmlDocument* createXmlDocument(JString* documentURI);

                    static JXmlDocument* createXmlDocument(JInputStream* in,jbool doValidate);

                    static JXmlDocument* createXmlDocument(JInputSource* in,jbool doValidate);

                    virtual void write(JOutputStream* out);

                    virtual void write(JWriter* out);

                    virtual void write(JWriter* out, JString* encoding);

                    virtual JXmlWriteContext* createWriteContext(JWriter* out);

                    virtual JXmlWriteContext* createWriteContext(JWriter* out, jint level);

                    virtual void writeXml(JXmlWriteContext* context);

                    virtual void writeChildrenXml(JXmlWriteContext* context);

                    virtual void checkChildType(jint type);

                    virtual void setSystemId(JString* uri);

                    virtual JString* getSystemId();

                    virtual JNode* appendChild(JNode* n);

                    virtual JNode* insertBefore(JNode* n, JNode* refNode);

                    virtual JNode* replaceChild(JNode* newChild, JNode* refChild);

                    virtual jshort getNodeType();

                    virtual JDocumentType* getDoctype();

                    virtual JDocumentType* setDoctype(JString* dtdPublicId,JString*  dtdSystemId,JString*  internalSubset);

                    virtual JElement* getDocumentElement();

                    virtual void setElementFactory(JElementFactory* factory);

                    virtual JElementFactory* getElementFactory();

                    virtual JElement* createElement(JString* tagName);

                    virtual JElement* createElementNS(JString* namespaceURI, JString* qualifiedName);

                    virtual JElementEx* createElementEx(JString* tagName);

                    virtual JElementEx* createElementEx(JString* uri, JString* tagName);

                    virtual JText* createTextNode(JString* text);

                    virtual JCDATASection* createCDATASection(JString* text);

                    virtual JTextNode* newText(JPrimitiveCharArray* buf, jint offset, jint len);

                    virtual JProcessingInstruction* createProcessingInstruction(JString* target, JString* instructions);

                    virtual JAttr* createAttribute(JString* name);

                    virtual JAttr* createAttributeNS(JString* namespaceURI, JString* qualifiedName);

                    virtual JComment* createComment(JString* data);

                    virtual JDocument* getOwnerDoc();

                    virtual JDOMImplementation* getImplementation();

                    virtual JDocumentFragment* createDocumentFragment();

                    virtual JEntityReference* createEntityReference(JString* name);

                    virtual JString* getNodeName();

                    virtual JNode* cloneNode(jbool deep);

                    virtual void changeNodeOwner(JNode* node);

                    virtual JElement* getElementById(JString* elementId);

                    virtual JElementEx* getElementExById(JString* id);

                    virtual JNode* importNode(JNode* importedNode, jbool deep);

                    virtual JString* getInputEncoding();

                    virtual JString* getXmlEncoding();

                    virtual jbool getXmlStandalone();

                    virtual void setXmlStandalone(jbool xmlStandalone);

                    virtual JString* getXmlVersion();

                    virtual void setXmlVersion(JString* xmlVersion);

                    virtual jbool getStrictErrorChecking();

                    virtual void setStrictErrorChecking(jbool strictErrorChecking);

                    virtual JString* getDocumentURI();

                    virtual void setDocumentURI(JString* documentURI);

                    virtual JNodeList* getElementsByTagName(JString* tagname);

                    virtual JNodeList* getElementsByTagNameNS(JString* namespaceURI,JString* localName);

                    virtual JNode* adoptNode(JNode* source);

                    virtual JDOMConfiguration* getDomConfig();

                    virtual void normalizeDocument();

                    virtual JNode* renameNode(JNode* n,JString* namespaceURI,JString* qualifiedName);

                    virtual ~JXmlDocument();
                };
            }
        }
    }
}

#endif
