#include "jcpp/xml/internal/tree/JElementNode.h"
#include "jcpp/xml/internal/tree/JTextNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/xml/internal/util/JXmlNames.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"

using namespace jcpp::xml::internal::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JElementNode::JElementNode():JElementNode2(getClazz(),null,null){
                }

                JElementNode::JElementNode(JString* name):JElementNode2(getClazz(),null,name){
                }

                JElementNode2* JElementNode::makeClone(){
                    JElementNode2* retval = new JElementNode(qName);
                    if (attributes != null) {
                        retval->attributes = new JAttributeSet(attributes, true);
                        retval->attributes->setOwnerElement(retval);
                    }
                    retval->setIdAttributeName(getIdAttributeName());
                    retval->setUserObject(getUserObject());
                    retval->ownerDocument = ownerDocument;
                    return retval;
                }

                void JElementNode::setTag(JString* t){
                    qName = t;
                }

                JString* JElementNode::getPrefix(){
                    return null;
                }

                JString* JElementNode::getLocalName(){
                    return null;
                }
                
                JElementNode::~JElementNode(){
                }
            }
        }
    }
}
