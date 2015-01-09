#include "jcpp/xml/internal/tree/JCommentNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JCommentNode::JCommentNode():JDataNode(getClazz()){
                }

                JCommentNode::JCommentNode(JString* data):JDataNode(getClazz(),data){
                }

                JCommentNode::JCommentNode(JPrimitiveCharArray* buf, jint offset, jint len):JDataNode(getClazz(),buf,offset,len){
                }

                jshort JCommentNode::getNodeType(){
                    return COMMENT_NODE;
                }

                void JCommentNode::writeXml(JXmlWriteContext* context){
                    JWriter*  out = context->getWriter();
                    out->write(new JString("<!--"));
                    if (data != null) {
                        jbool sawDash = false;
                        jint length = data->size();

                        for (jint i = 0; i < length; i++) {
                            if (data->getChar(i) == '-') {
                                if (sawDash){
                                    out->write(' ');
                                
                                }else {
                                    sawDash = true;
                                    out->write('-');
                                    continue;
                                }
                            }
                            sawDash = false;
                            out->write(data->getChar(i));
                        }
                        if (data->getChar(data->size() - 1) == '-'){
                            out->write(' ');
                        }
                    }
                    out->write(new JString("-->"));
                }

                JNode* JCommentNode::cloneNode(jbool deep){
                    JCommentNode* retval = new JCommentNode(data, 0, data->size()); 
                    retval->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    return retval;
                }

                JString* JCommentNode::getNodeName(){
                    return new JString("#comment");
                }

                JCommentNode::~JCommentNode(){
                }
            }
        }
    }
}
