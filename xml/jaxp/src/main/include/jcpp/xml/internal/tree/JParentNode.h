#ifndef JCPP_XML_INTERNAL_TREE_PARENT_NODE_H
#define JCPP_XML_INTERNAL_TREE_PARENT_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "jcpp/xml/internal/tree/JNodeBase.h"
#include "jcpp/xml/internal/tree/JTreeWalker.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JDocument.h"
#include "org/w3c/dom/JNamedNodeMap.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.ParentNode", simpleName="ParentNode");
                class JCPP_EXPORT JParentNode : public JNodeBase{
                protected:

                	// @Class(canonicalName="javax.xml.internal.tree.ParentNode$TagList", simpleName="ParentNode$TagList");
                    class JTagList : public JObject, public JNodeList {
                    protected:
                        JParentNode* parentNode;
                        JString* tag;
                        jint lastMutationCount;
                        jint lastIndex;
                        JTreeWalker* lastWalker;
                        JTagList(JClass* _class,JParentNode* parentNode,JString* tag);
                        friend class JTagListNS;

                    public:
                        JTagList(JParentNode* parentNode,JString* tag);

                        static JClass* getClazz();

                        virtual jint getLastMutationCount();

                        virtual JNode* item(jint i);

                        virtual jint getLength();

                        virtual ~JTagList();
                    };

                    // @Class(canonicalName="javax.xml.internal.tree.ParentNode$TagListNS", simpleName="ParentNode$TagListNS");
                    class JTagListNS : public JTagList {
                    protected:
                        JString* namespaceURI;

                    public:                        
                        JTagListNS(JParentNode* parentNode,JString* namespaceURI, JString* localName);

                        static JClass* getClazz();

                        virtual JNode* item(jint i);

                        virtual jint getLength();

                        virtual ~JTagListNS();
                    };

                    JPrimitiveObjectArray* children;
                    jint length;
                    JParentNode(JClass* _class);
                    friend class JParentNode::JTagList;
                    friend class JParentNode::JTagListNS;
                    friend class JTagListNSClass;

                public:
                    static JClass* getClazz();

                    virtual void trimToSize();

                    virtual void reduceWaste();

                    virtual void writeChildrenXml(JXmlWriteContext* context);
   
                    virtual void checkChildType(jint type)=0;

                    virtual jbool hasChildNodes();

                    virtual JNode* getFirstChild();

                    virtual JNode* getLastChild();

                    virtual jint getLength();

                    virtual JNode* item(jint i);

                    virtual JNodeBase* checkDocument(JNode* newChild);

                    virtual void checkNotAncestor(JNode* newChild);

                    virtual void mutated();

                    virtual void consumeFragment(JNode* fragment, JNode* before);

                    virtual JNode* appendChild(JNode* newChild);

                    virtual JNode* insertBefore(JNode* newChild, JNode* refChild);

                    virtual JNode* replaceChild(JNode* newChild, JNode* refChild);

                    virtual JNode* removeChild(JNode* oldChild);

                    virtual JNodeList* getElementsByTagName(JString* tagname);

                    virtual JNodeList* getElementsByTagNameNS(JString* namespaceURI,JString* localName);

                    virtual jint getIndexOf(JNode* maybeChild);

                    virtual void normalize();

                    virtual jint removeWhiteSpaces(JPrimitiveCharArray* buf);

                    virtual ~JParentNode();
                };
            }
        }
    }
}

#endif
