#ifndef JCPP_XML_INTERNAL_TREE_DATA_NODE_H
#define JCPP_XML_INTERNAL_TREE_DATA_NODE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "jcpp/xml/internal/tree/JNodeBase.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JCharacterData.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

            	// @Class(canonicalName="javax.xml.internal.tree.DataNode", simpleName="DataNode");
                class JCPP_EXPORT JDataNode : public JNodeBase, public virtual JCharacterData{
                protected:

                	// @Class(canonicalName="javax.xml.internal.tree.DataNode$NodeListImpl", simpleName="DataNode$NodeListImpl");
                    class JNodeListImpl : public JObject, public JNodeList {
                    public:
                        JNodeListImpl();

                        static JClass* getClazz();

                        virtual JNode* item(jint i);

                        virtual jint getLength();

                        ~JNodeListImpl();
                    };

                    static JNodeListImpl* childNodes;

                    JPrimitiveCharArray* data;
                    JDataNode(JClass* _class);
                    JDataNode(JClass* _class,JPrimitiveCharArray* buf, jint offset, jint len);
                    JDataNode(JClass* _class,JString* s);


                public:
                    static JClass* getClazz();

                    virtual JPrimitiveCharArray* getText();

                    virtual void setText(JPrimitiveCharArray* buf);

                    virtual JString* toString();

                    virtual JString* getData();

                    virtual void setData(JString* data);

                    virtual jint getLength();

                    virtual JString* substringData(jint offset, jint count);

                    virtual void appendData(JString* newData); 

                    virtual void insertData(jint offset, JString* newData);

                    virtual void deleteData(jint offset, jint count);

                    virtual void replaceData(jint offset, jint count, JString* arg);

                    virtual JNodeList* getChildNodes();

                    virtual JString* getNodeValue();

                    virtual void setNodeValue(JString* value);

                    virtual ~JDataNode();
                };
            }
        }
    }
}

#endif
