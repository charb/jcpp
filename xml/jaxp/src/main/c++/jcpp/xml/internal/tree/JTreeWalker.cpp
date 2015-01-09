#include "jcpp/xml/internal/tree/JTreeWalker.h"
#include "jcpp/xml/internal/tree/JNodeBase.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JInternalError.h"
#include "org/w3c/dom/JNode.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JTreeWalker::JTreeWalker(JNode* initial):JObject(getClazz()){
                    if (initial == null) {
                        throw new JIllegalArgumentException(new JString("Initial node null"));
                    }
                    if (!(dynamic_cast<JObject*>(initial)->isInstanceOf(JNodeBase::getClazz()))) { 
                        throw new JIllegalArgumentException(new JString("Initial node is not pf type NodeBase"));
                    }
                    current = initial;
                    startPoint = initial;
                }

                JNode* JTreeWalker::getCurrent(){
                    return current;
                }

                JNode* JTreeWalker::getNext(){
                    JNode* next=null;

                    if (current == null){
                        return null;
                    }

                    switch (current->getNodeType()) {
                      case JNode::DOCUMENT_FRAGMENT_NODE:
                      case JNode::DOCUMENT_NODE:
                      case JNode::ELEMENT_NODE:
                      case JNode::ENTITY_REFERENCE_NODE:
                        next = current->getFirstChild();
                        if (next != null) {
                            current = next;
                            return next;
                        }

                      case JNode::ATTRIBUTE_NODE:
                      case JNode::CDATA_SECTION_NODE:
                      case JNode::COMMENT_NODE:
                      case JNode::DOCUMENT_TYPE_NODE:
                      case JNode::ENTITY_NODE:
                      case JNode::NOTATION_NODE:
                      case JNode::PROCESSING_INSTRUCTION_NODE:
                      case JNode::TEXT_NODE:
                        for (JNode* here = current; here != null && here != startPoint; here = here->getParentNode()) {
                            next = here->getNextSibling ();
                            if (next != null) {
                                current = next;
                                return next;
                            }
                        }
                        current = null;
                        return null;
                    }
                    throw new JInternalError(new JString("unknown node type where traversing tree"));
                }

                JElement* JTreeWalker::getNextElement(JString* tag){
                    for (JNode* next = getNext();next != null;next = getNext()) {
                        if (next->getNodeType() == JNode::ELEMENT_NODE && (tag == null || tag->equals(next->getNodeName()))){
                            return dynamic_cast<JElement*>(next);
                        }
                    }
                    current = null;
                    return null;
                }

                JElement* JTreeWalker::getNextElement(JString* nsURI, JString* localName){
                    for (JNode* next = getNext(); next != null; next = getNext()) {
                        if ( next->getNodeType() == JNode::ELEMENT_NODE && 
                            (nsURI == null || nsURI->equals(next->getNamespaceURI())) && 
                            (localName == null || localName->equals(next->getLocalName()))) {
                            return dynamic_cast<JElement*>(next);
                        }
                    }
                    current = null;
                    return null;
                }

                void JTreeWalker::reset(){
                    current = startPoint;
                }

                JNode* JTreeWalker::removeCurrent(){
                    if (current == null){
                        throw new JIllegalStateException(new JString("removing null node"));
                    }

                    JNode* toRemove = current;
                    JNode* parent = current->getParentNode();
                    JNode* retval = null;

                    if (parent == null){
                        throw new JIllegalStateException(new JString("null parent while removing node"));
                    }
                    
                    for (JNode* here = current; here != null && here != startPoint; here = here->getParentNode()) {
                        retval = here->getNextSibling ();
                        if (retval != null) {
                            current = retval;
                            break;
                        }
                    }
                    parent->removeChild (toRemove);
                    return retval;
                }

                JTreeWalker::~JTreeWalker(){
                }
            }
        }
    }
}
