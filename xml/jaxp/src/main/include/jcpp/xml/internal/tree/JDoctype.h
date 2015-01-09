#ifndef JCPP_XML_INTERNAL_TREE_DOC_TYPE_H
#define JCPP_XML_INTERNAL_TREE_DOC_TYPE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "jcpp/xml/internal/tree/JNodeBase.h"
#include "jcpp/util/JVector.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JDocumentType.h"
#include "org/w3c/dom/JNamedNodeMap.h"
#include "org/w3c/dom/JNotation.h"
#include "org/w3c/dom/JEntity.h"

using namespace org::w3c::dom;
using namespace jcpp::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.Doctype", simpleName="Doctype");
                class JCPP_EXPORT JDoctype : public JNodeBase, public virtual JDocumentType{
                protected:

                	// @Class(canonicalName="javax.xml.internal.tree.Doctype$NotationNode", simpleName="Doctype$NotationNode");
                    class JCPP_EXPORT JNotationNode : public  JNodeBase, public virtual JNotation{
                    protected:
                        JString*  notation;
                        JString*  publicId;
                        JString*  systemId;
                        friend class JDoctype;
                    public:
                        JNotationNode(JString* name, JString* pub, JString* sys);

                        static JClass* getClazz();

                        virtual JString* getPublicId();

                        virtual JString* getSystemId();

                        virtual jshort getNodeType();

                        virtual JString* getNodeName();

                        virtual JNode* cloneNode(jbool ignored);

                        virtual void writeXml(JXmlWriteContext* context);

                        virtual ~JNotationNode();
                    };

                    // @Class(canonicalName="javax.xml.internal.tree.Doctype$EntityNode", simpleName="Doctype$EntityNode");
                    class JCPP_EXPORT JEntityNode : public JNodeBase , public virtual JEntity{
                    protected:
                        JString*  entityName;
                        JString*  publicId;
                        JString*  systemId;
                        JString*  notation;
                        JString*  value;
                        friend class JDoctype;

                    public:
                        JEntityNode(JString* name, JString* pub, JString* sys, JString* snot);

                        JEntityNode(JString* name, JString* value);

                        static JClass* getClazz();

                        virtual JString* getNodeName();

                        virtual jshort getNodeType();

                        virtual JString* getPublicId();

                        virtual JString* getSystemId();

                        virtual JString* getNotationName();

                        virtual JString* getInputEncoding();

                        virtual JString* getXmlEncoding();

                        virtual JString* getXmlVersion();

                        virtual JNode* cloneNode(jbool ignored);

                        virtual void writeXml(JXmlWriteContext* context);

                        virtual ~JEntityNode();
                    };

                    // @Class(canonicalName="javax.xml.internal.tree.Doctype$Nodemap", simpleName="Doctype$Nodemap");
                    class JCPP_EXPORT JNodemap : public JObject, public JNamedNodeMap{
                    protected:
                        jbool readonly;
                        JVector* list;
                        friend class JDoctype;
                    
                    public:
                        JNodemap();

                        static JClass* getClazz();

                        virtual JNode* getNamedItem(JString* name);

                        virtual JNode* getNamedItemNS(JString* namespaceURI, JString* localName);

                        virtual jint getLength();

                        virtual JNode* item(jint index);

                        virtual JNode* removeNamedItem(JString* name);

                        virtual JNode* removeNamedItemNS(JString* namespaceURI, JString* localName);

                        virtual JNode* setNamedItem(JNode* item);

                        virtual JNode* setNamedItemNS(JNode* arg);

                        virtual ~JNodemap();
                    };

                    JString* name;
                    JNodemap* entities;
                    JNodemap* notations;
                    JString*  publicId;
                    JString*  systemId;
                    JString*  internalSubset;
                    
                public:
                    JDoctype(JString* pub, JString* sys, JString* subset);

                    JDoctype(JString* name, JString* publicId, JString* systemId,JString* internalSubset);

                    static JClass* getClazz();

                    virtual void setPrintInfo(JString* pub, JString* sys, JString* subset);

                    virtual void writeXml(JXmlWriteContext* context);

                    virtual jshort getNodeType();

                    virtual JString* getName();

                    virtual JString* getNodeName();

                    virtual JNode* cloneNode(jbool deep);

                    virtual JNamedNodeMap* getEntities();

                    virtual JNamedNodeMap* getNotations();

                    virtual JString* getPublicId();

                    virtual JString* getSystemId();

                    virtual JString* getInternalSubset();

                    virtual void setOwnerDocument(JXmlDocument* doc);

                    virtual void addNotation(JString* name, JString* pub, JString* sys);

                    virtual void addEntityNode(JString* name, JString* pub, JString* sys, JString* snot);

                    virtual void addEntityNode(JString* name, JString* value);

                    virtual void setReadonly();

                    virtual JString* getNodeValue();

                    virtual void setNodeValue(JString* value);

                    virtual JNode* getParentNode();

                    virtual JNodeList* getChildNodes();

                    virtual JNode* getFirstChild();

                    virtual JNode* getLastChild();
        
                    virtual JNode* getPreviousSibling();

                    virtual JNode* getNextSibling();

                    virtual JNamedNodeMap* getAttributes();

                    virtual JDocument* getOwnerDocument();

                    virtual JNode* insertBefore(JNode* newChild,JNode* refChild);

                    virtual JNode* replaceChild(JNode* newChild,JNode* oldChild);

                    virtual JNode* removeChild(JNode* oldChild);
        
                    virtual JNode* appendChild(JNode* newChild);

                    virtual jbool hasChildNodes();

                    virtual void normalize();

                    virtual jbool isSupported(JString* feature,JString* version);

                    virtual JString* getNamespaceURI();

                    virtual JString* getPrefix();

                    virtual void setPrefix(JString* prefix);

                    virtual JString* getLocalName();

                    virtual jbool hasAttributes();

                    virtual ~JDoctype();
                };
            }
        }
    }
}

#endif
