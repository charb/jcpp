#include "jcpp/xml/internal/tree/JPINode.h"
#include "jcpp/xml/internal/tree/JTextNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JPINode::JPINode():JNodeBase(getClazz()){
                    target=null;
                    data=null;
                }

                JPINode::JPINode(JString* target,JString* text):JNodeBase(getClazz()){
                    data=text->toCharArray();
                    this->target=target;
                }
                
                JPINode::JPINode(JString* target, JPrimitiveCharArray* buf, jint offset, jint len):JNodeBase(getClazz()){
                    data = new JPrimitiveCharArray(len);
                    JSystem::arraycopy(buf, offset, data, 0, len);
                    this->target = target;
                }

                jshort JPINode::getNodeType(){
                    return PROCESSING_INSTRUCTION_NODE;
                }

                JString* JPINode::getTarget(){
                    return target;
                }

                void JPINode::setTarget(JString* target){
                    this->target = target;
                }

                JString* JPINode::getData(){
                    return new JString(data);
                }

                void JPINode::setData(JString* data){
                    if (isReadonly ()){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    
                    this->data = data->toCharArray(); 
                }

                JString* JPINode::getNodeValue(){
                    return getData();
                }

                void JPINode::setNodeValue(JString* data){
                    setData(data);
                }

                void JPINode::writeXml(JXmlWriteContext* context){
                    JWriter* out = context->getWriter();
                    out->write(new JString("<?"));
                    out->write(target);
                    if (data != null) {
                        out->write(' ');
                        out->write(data);
                    }
                    out->write(new JString("?>"));
                }

                JNode* JPINode::cloneNode(jbool deep){
                    JPINode* retval = new JPINode(target, data, 0, data->size()); 
                    retval->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    return retval;
                }

                JString* JPINode::getNodeName(){
                    return target;
                }

                JPINode::~JPINode(){
                }
            }
        }
    }
}
