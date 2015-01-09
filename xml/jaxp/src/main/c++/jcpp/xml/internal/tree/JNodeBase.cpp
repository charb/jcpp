#include "jcpp/xml/internal/tree/JNodeBase.h"
#include "jcpp/xml/internal/tree/JTreeWalker.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/xml/internal/tree/JElementNode2.h"
#include "jcpp/xml/internal/tree/JDOMImplementationImpl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JException.h"
#include "org/w3c/dom/JDOMException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JNodeBase::JNodeBase(JClass* _class):JObject(_class){
                    parent=null;
                    parentIndex=-1;
                    ownerDocument=null;
                    readonly=false;
                }

                JParentNode* JNodeBase::getParentImpl(){
                    return parent;
                }

                jbool JNodeBase::isReadonly(){
                    return readonly;
                }

                void JNodeBase::setReadonly(jbool deep){
                    readonly = true;
                    if (deep) {
                        JTreeWalker*  walker = new JTreeWalker(this);
                        JNode* next=null;
                        while ((next = walker->getNext()) != null){
                            (dynamic_cast<JNodeBase*>(next))->setReadonly(false);
                        }
                    }
                }

                JString* JNodeBase::getLanguage(){
                    return getInheritedAttribute(new JString("xml:lang"));
                }

                JString* JNodeBase::getInheritedAttribute(JString* name){
                    JNodeBase* current = this;
                    JAttr* value = null;

                    do {
                        if (current->isInstanceOf(JElementNode2::getClazz())) {
                            JElementNode2* e = dynamic_cast<JElementNode2*>(current);
                            if ((value = e->getAttributeNode (name)) != null){
                                break;
                            }
                        }
                        current = current->getParentImpl();
                    } while (current != null);
                    if (value != null){
                        return value->getValue();
                    }
                    return null;
                }

                void JNodeBase::writeChildrenXml(JXmlWriteContext* context){
                }

                JNode* JNodeBase::getParentNode(){
                    return parent;
                }

                void JNodeBase::setParentNode(JParentNode* arg, jint index){
                    if (parent != null && arg != null){
                        parent->removeChild (this);
                    }
                    parent = arg;
                    parentIndex = index;
                }

                void JNodeBase::setOwnerDocument(JXmlDocument* doc){
                    ownerDocument=doc;
                }

                JDocument* JNodeBase::getOwnerDocument(){
                    return ownerDocument;
                }

                jbool JNodeBase::hasChildNodes(){
                    return false;
                }

                void JNodeBase::setNodeValue(JString* value){
                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                }

                JString* JNodeBase::getNodeValue(){
                    return null;
                }

                JNode* JNodeBase::getFirstChild(){
                    return null;
                }

                jint JNodeBase::getLength(){
                    return 0;
                }

                JNode* JNodeBase::item(jint i){
                    return null;
                }

                JNodeList* JNodeBase::getChildNodes(){
                    return this;
                }

                JNode* JNodeBase::getLastChild(){
                    return null;
                }

                JNode* JNodeBase::appendChild(JNode* newChild){
                    throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                }

                JNode* JNodeBase::insertBefore(JNode* newChild, JNode* refChild){
                    throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                }

                JNode* JNodeBase::replaceChild(JNode* newChild, JNode* refChild){
                    throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                }

                JNode* JNodeBase::removeChild(JNode* oldChild){
                    throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                }

                JNode* JNodeBase::getNextSibling(){
                    if (parent == null){
                        return null;
                    }
                    if (parentIndex < 0 || parent->item(parentIndex) != this){
                        parentIndex = parent->getIndexOf(this);
                    }
                    return parent->item(parentIndex + 1);
                }

                JNode* JNodeBase::getPreviousSibling(){
                    if (parent == null){
                        return null;
                    }
                    if (parentIndex < 0 || parent->item (parentIndex) != this){
                        parentIndex = parent->getIndexOf (this);
                    }
                    return parent->item(parentIndex - 1);
                }

                JNamedNodeMap* JNodeBase::getAttributes(){
                    return null;
                }

                void JNodeBase::normalize(){
                }

                jbool JNodeBase::isSupported(JString* feature, JString* version){
                    return JDOMImplementationImpl::hasFeature0(feature, version);
                }

                JString* JNodeBase::getNamespaceURI(){
                    return null;
                }

                JString* JNodeBase::getPrefix(){
                    return null;
                }

                void JNodeBase::setPrefix(JString* prefix){
                    throw new JDOMException(JDOMException::NAMESPACE_ERR);
                }

                JString* JNodeBase::getLocalName(){
                    return null;
                }

                JString* JNodeBase::getBaseURI(){
                    throw new JException(new JString("TODO not implemented"));
                }

                jshort JNodeBase::compareDocumentPosition(JNode* other){
                    throw new JException(new JString("TODO not implemented"));
                }

                JString* JNodeBase::getTextContent(){
                    throw new JException(new JString("TODO not implemented"));
                }

                void JNodeBase::setTextContent(JString* textContent){
                    throw new JException(new JString("TODO not implemented"));
                }

                jbool JNodeBase::isSameNode(JNode* other){
                    throw new JException(new JString("TODO not implemented"));
                }

                JString* JNodeBase::lookupPrefix(JString* namespaceURI){
                    throw new JException(new JString("TODO not implemented"));
                }

                jbool JNodeBase::isDefaultNamespace(JString* namespaceURI){
                    throw new JException(new JString("TODO not implemented"));
                }

                JString* JNodeBase::lookupNamespaceURI(JString* prefix){
                    throw new JException(new JString("TODO not implemented"));
                }

                jbool JNodeBase::isEqualNode(JNode* arg){
                    throw new JException(new JString("TODO not implemented"));
                }

                JObject* JNodeBase::getFeature(JString* feature,JString* version){
                    throw new JException(new JString("TODO not implemented"));
                }

                JObject* JNodeBase::setUserData(JString* key,JObject* data,JUserDataHandler* handler){
                    throw new JException(new JString("TODO not implemented"));
                }

                JObject* JNodeBase::getUserData(JString* key){
                    throw new JException(new JString("TODO not implemented"));
                }

                jbool JNodeBase::hasAttributes(){
                    return false;
                }

                jint JNodeBase::getIndexOf(JNode* maybeChild){
                    return -1;
                }

                JNodeBase::~JNodeBase(){
                }
            }
        }
    }
}
