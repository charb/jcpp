#include "jcpp/xml/internal/tree/JCDataNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JCDataNode::JCDataNode():JTextNode(getClazz()){
                }

                JCDataNode::JCDataNode(JPrimitiveCharArray* buf, jint offset, jint len):JTextNode(getClazz(),buf,offset,len){
                }

                JCDataNode::JCDataNode(JString* s):JTextNode(getClazz(),s){
                }

                void JCDataNode::writeXml(JXmlWriteContext* context){
                    JWriter*  out = context->getWriter();
                    out->write(new JString("<![CDATA["));
                    for (jint i = 0; i < data->size(); i++) {
                        jchar c = data->getChar(i);
                        if (c == ']') {
                            if ((i + 2) < data->size()
                                && data->getChar(i + 1) == ']'
                                && data->getChar(i + 2) == '>') {
                                out->write(new JString("]]]><![CDATA["));
                                continue;
                            }
                        }
                        out->write(c);
                    }
                    out->write(new JString("]]>"));
                }

                jshort JCDataNode::getNodeType(){
                    return CDATA_SECTION_NODE;
                }

                JNode* JCDataNode::cloneNode(jbool deep){
                    JCDataNode* retval = new JCDataNode(data, 0, data->size());
                    retval->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    return retval;
                }

                JString* JCDataNode::getNodeName(){
                    return new JString("#cdata-section");
                }

                JCDataNode::~JCDataNode(){
                }
            }
        }
    }
}
