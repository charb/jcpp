#include "jcpp/xml/internal/tree/JTextNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"
#include "jcpp/lang/JException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JTextNode::JTextNode(JClass* _class):JDataNode(_class){
                }

                JTextNode::JTextNode(JClass* _class,JPrimitiveCharArray* buf, jint offset, jint len):JDataNode(_class,buf,offset,len){
                }

                JTextNode::JTextNode(JClass* _class,JString* s):JDataNode(_class,s){
                }

                JTextNode::JTextNode():JDataNode(getClazz()){
                }

                JTextNode::JTextNode(JPrimitiveCharArray* buf, jint offset, jint len):JDataNode(getClazz(),buf,offset,len){
                }

                JTextNode::JTextNode(JString* s):JDataNode(getClazz(),s){
                }

                void JTextNode::writeXml(JXmlWriteContext* context){
                    JWriter*  out = context->getWriter();
                    jint start = 0;
                    jint last = 0;

                    if (data == null){
                        return; 
                    }

                    while (last < data->size()) {
                        jchar c = data->getChar(last);

                        if (c == '<') {       
                            out->write(data, start, last - start);
                            start = last + 1;
                            out->write(new JString("&lt;"));

                        } else if (c == '>') {
                            out->write(data, start, last - start);
                            start = last + 1;
                            out->write(new JString("&gt;"));
                        
                        } else if (c == '&') {
                            out->write(data, start, last - start);
                            start = last + 1;
                            out->write(new JString("&amp;"));
                        }
                        last++;
                    }
                    out->write(data, start, last - start);
                }

                void JTextNode::joinNextText(){
                    JNode* next = getNextSibling();
                    JPrimitiveCharArray* tmp=null;
                    JPrimitiveCharArray* nextText=null;

                    if (next == null || next->getNodeType () != TEXT_NODE){
                        return;
                    }
                    getParentNode()->removeChild (next);

                    nextText = (dynamic_cast<JTextNode*>(next))->getText ();
                    tmp = new JPrimitiveCharArray(data->size() + nextText->size());
                    JSystem::arraycopy (data, 0, tmp, 0, data->size());
                    JSystem::arraycopy (nextText, 0, tmp, data->size(), nextText->size());
                    data = tmp;
                }

                jshort JTextNode::getNodeType(){
                    return TEXT_NODE;
                }

                JText* JTextNode::splitText(jint offset){
                    JTextNode* retval=null;
                    JPrimitiveCharArray* delta=null;

                    if (isReadonly ()){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                   
                    retval = new JTextNode(data, offset, data->size() - offset);
                    
                    getParentNode()->insertBefore(retval, getNextSibling());
                    delta = new JPrimitiveCharArray(offset);
                    JSystem::arraycopy(data, 0, delta, 0, offset);
                    data = delta;
                    return retval;
                }

                JNode* JTextNode::cloneNode(jbool deep){
                    JTextNode* retval = new JTextNode(data, 0, data->size());
                    retval->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    return dynamic_cast<JNode*>(retval);
                }

                JString* JTextNode::getNodeName(){
                    return new JString("#text");
                }

                jbool JTextNode::isElementContentWhitespace(){
                    throw new JException(new JString("TODO not implemented"));
                }

                JString* JTextNode::getWholeText(){
                    throw new JException(new JString("TODO not implemented"));
                }

                JText* JTextNode::replaceWholeText(JString* content){
                    throw new JException(new JString("TODO not implemented"));
                }

                JTextNode::~JTextNode(){
                }
            }
        }
    }
}
