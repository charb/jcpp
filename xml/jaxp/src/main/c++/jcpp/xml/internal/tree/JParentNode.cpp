#include "jcpp/xml/internal/tree/JParentNode.h"
#include "jcpp/xml/internal/tree/JTextNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JParentNode::JParentNode(JClass* _class):JNodeBase(_class){
                   children=null;
                   length=0;
                }

                JParentNode::JTagList::JTagList(JClass* _class,JParentNode* parentNode,JString* tag):JObject(_class){
                    this->parentNode=parentNode;
                    this->tag=tag;
                    lastMutationCount=0;
                    lastIndex=0;
                    lastWalker=null;
                }

                JParentNode::JTagList::JTagList(JParentNode* parentNode,JString* tag):JObject(getClazz()){
                    this->parentNode=parentNode;
                    this->tag=tag;
                    lastMutationCount=0;
                    lastIndex=0;
                    lastWalker=null;
                }

                jint JParentNode::JTagList::getLastMutationCount(){
                    JXmlDocument* doc = dynamic_cast<JXmlDocument*>(parentNode->getOwnerDocument());
                    return (doc == null) ? 0 : doc->mutationCount;
                }

                JNode* JParentNode::JTagList::item(jint i){
                    if (i < 0){
                        return null;
                    }

                    jint temp = getLastMutationCount ();

                    if (lastWalker != null) {
                        if (i < lastIndex || temp != lastMutationCount){
                            lastWalker = null;
                        }
                    }

                    if (lastWalker == null) {
                        lastWalker = new JTreeWalker(parentNode);
                        lastIndex = -1;
                        lastMutationCount = temp;
                    }

                    if (i == lastIndex){
                        return lastWalker->getCurrent();
                    }

                    JNode* node = null;

                    while (i > lastIndex && (node = lastWalker->getNextElement(tag)) != null) {
                        lastIndex++;
                    }

                    if (node == null) {
                        lastWalker = null;
                    }
                    return node;
                }

                jint  JParentNode::JTagList::getLength(){
                    JTreeWalker*  walker = new JTreeWalker(parentNode);
                    JNode* node = null;
                    jint retval;

                    for (retval = 0; (node = walker->getNextElement(tag)) != null; retval++){
                        continue;
                    }
                    return retval;
                }

                JParentNode::JTagList::~JTagList(){
                }
                     
                JParentNode::JTagListNS::JTagListNS(JParentNode* parentNode,JString* namespaceURI, JString* localName):JTagList(getClazz(),parentNode,localName){
                    this->namespaceURI=namespaceURI;
                }

                JNode* JParentNode::JTagListNS::item(jint i){
                    if (i < 0) {
                        return null;
                    }

                    jint temp = getLastMutationCount();

                    if (lastWalker != null) {
                        if (i < lastIndex || temp != lastMutationCount) {
                            lastWalker = null;
                        }
                    }

                    if (lastWalker == null) {
                        lastWalker = new JTreeWalker(parentNode);
                        lastIndex = -1;
                        lastMutationCount = temp;
                    }

                    if (i == lastIndex) {
                        return lastWalker->getCurrent();
                    }

                    JNode* node = null;

                    while (i > lastIndex && (node = lastWalker->getNextElement(namespaceURI, tag)) != null) {
                        lastIndex++;
                    }

                    if (node == null) {
                        lastWalker = null;
                    }
                    return node;
                }

                jint JParentNode::JTagListNS::getLength(){
                    JTreeWalker* walker = new JTreeWalker(parentNode);
                    jint count=0;
                    for (count = 0; walker->getNextElement(namespaceURI, tag) != null;count++) {
                    }
                    return count;
                }

                JParentNode::JTagListNS::~JTagListNS(){
                }

                void JParentNode::trimToSize(){
                    if (length == 0){
                        children = null;
                    
                    }else if (children->size() != length) {
                        JPrimitiveObjectArray* temp= new JPrimitiveObjectArray(JNodeBase::getClazz(),length);
                        JSystem::arraycopy (children, 0, temp, 0, length);
                        children = temp;
                    }
                }

                void JParentNode::reduceWaste(){
                    if (children == null){
                        return;
                    }

                    if ((children->size() - length) > 6){
                        trimToSize ();
                    }
                }

                void JParentNode::writeChildrenXml(JXmlWriteContext* context){
                    if (children == null){
                        return;
                    }

                    jint oldIndent = 0;
                    jbool preserve = true;
                    jbool pureText = true;

                    if (getNodeType () == ELEMENT_NODE) {
                        preserve = (new JString("preserve"))->equals(getInheritedAttribute(new JString("xml:space")));
                        oldIndent = context->getIndentLevel ();
                    }

                    if (!preserve){
                        context->setIndentLevel(oldIndent + 2);
                        for (jint i = 0; i < length; i++) {
                            JNodeBase* nb=dynamic_cast<JNodeBase*>(children->get(i));
                            if (!preserve && nb->getNodeType() != TEXT_NODE) {
                                context->printIndent ();
                                pureText = false;
                            }
                            nb->writeXml (context);
                        }
                    }
                    if (!preserve) {
                        context->setIndentLevel(oldIndent);
                        if (!pureText){
                            context->printIndent();
                        }
                    }
                }

                jbool JParentNode::hasChildNodes(){
                    return length > 0;
                }

                JNode* JParentNode::getFirstChild(){
                    if (length == 0){
                        return null;
                    }
                    return dynamic_cast<JNode*>(children->get(0));
                }

                JNode* JParentNode::getLastChild(){
                    if (length == 0){
                        return null;
                    }
                    return dynamic_cast<JNode*>(children->get(length - 1));
                }

                jint JParentNode::getLength(){
                    return length;
                }

                JNode* JParentNode::item(jint i){
                    if (length == 0 || i >= length){
                        return null;
                    }
                    try {
                        return dynamic_cast<JNode*>(children->get(i));
                    } catch (JArrayIndexOutOfBoundsException* e) {
                        return null;
                    }
                }

                JNodeBase* JParentNode::checkDocument(JNode* newChild){
                    if (newChild == null){
                        throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }

                    if (!(dynamic_cast<JObject*>(newChild)->isInstanceOf(JNodeBase::getClazz()))){
                        throw new JDOMException(JDOMException::WRONG_DOCUMENT_ERR);
                    }

                    JDocument*    owner = newChild->getOwnerDocument ();
                    JXmlDocument* myOwner = ownerDocument;
                    JNodeBase*    child = dynamic_cast<JNodeBase*>(newChild);

                    if (myOwner == null && isInstanceOf(JXmlDocument::getClazz())){
                        myOwner = dynamic_cast<JXmlDocument*>(this);
                    }

                    if (owner != null && owner != myOwner){
                        throw new JDOMException(JDOMException::WRONG_DOCUMENT_ERR);
                    }
                    
                    if (owner == null) {
                        child->setOwnerDocument (myOwner);
                    }

                    if (child->hasChildNodes ()) {
                        for (jint i = 0; true; i++) {
                            JNode* node = child->item (i);
                            if (node == null){
                                break;
                            }
                            if (node->getOwnerDocument () == null){
                                (dynamic_cast<JNodeBase*>(node))->setOwnerDocument (myOwner);

                            }else if (node->getOwnerDocument () != myOwner){
                                throw new JDOMException(JDOMException::WRONG_DOCUMENT_ERR);
                            }
                        }
                    }

                    return child;
                }

                void JParentNode::checkNotAncestor(JNode* newChild){
                    if (!newChild->hasChildNodes()){
                        return;
                    }
                    JNode* ancestor = this;
                    while (ancestor != null) {
                        if (newChild == ancestor){
                            throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                        }
                        ancestor = ancestor->getParentNode ();
                    }
                }

                void JParentNode::mutated(){
                    JXmlDocument* doc = ownerDocument;
                    if (doc == null && isInstanceOf(JXmlDocument::getClazz())){
                        doc = dynamic_cast<JXmlDocument*>(this);
                    }
                    if (doc != null){
                        doc->mutationCount++;
                    }
                }

                void JParentNode::consumeFragment(JNode* fragment, JNode* before){
                    JParentNode*  frag =dynamic_cast<JParentNode*>(fragment);
                    JNode* temp=null;

                    for (jint i = 0; (temp = frag->item(i)) != null; i++) {
                        checkNotAncestor(temp);
                        checkChildType(temp->getNodeType ());
                    }

                    while ((temp = frag->item(0)) != null) {
                        insertBefore(temp, before);
                    }
                }

                JNode* JParentNode::appendChild(JNode* newChild){
                    JNodeBase* child=null;

                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    child=checkDocument(newChild);

                    if (newChild->getNodeType () == DOCUMENT_FRAGMENT_NODE) {
                        consumeFragment(newChild, null);
                        return newChild;
                    }

                    checkNotAncestor(newChild);
                    checkChildType(child->getNodeType());

                    if (children == null){
                        children = new JPrimitiveObjectArray(JNodeBase::getClazz(),3);
                    
                    }else if (children->size() == length) {
                        JPrimitiveObjectArray* temp = new JPrimitiveObjectArray(JNodeBase::getClazz(),length * 2);
                        JSystem::arraycopy(children, 0, temp, 0, length);
                        children = temp;
                    }

                    child->setParentNode (this, length);
                    children->set(length++, child);
                    mutated();
                    return child;
                }

                JNode* JParentNode::insertBefore(JNode* newChild, JNode* refChild){
                    JNodeBase* child=null;

                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    if (refChild == null){
                        return appendChild (newChild);
                    }
                    if (length == 0){
                        throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                    }

                    child = checkDocument(newChild);

                    if (newChild->getNodeType() == DOCUMENT_FRAGMENT_NODE) {
                        consumeFragment(newChild, refChild);
                        return newChild;
                    }

                    checkNotAncestor(newChild);
                    checkChildType(newChild->getNodeType ());

                    for (jint i = 0; i < length; i++) {
                        if (children->get(i) == dynamic_cast<JObject*>(newChild)) {
                            removeChild(newChild);
                            break;
                        }
                    }

                    if (children->size() == length) {
                        JPrimitiveObjectArray* temp = new JPrimitiveObjectArray(JNodeBase::getClazz(),length * 2);
                        JSystem::arraycopy(children, 0, temp, 0, length);
                        children = temp;
                    }

                    for (jint i = 0; i < length; i++) {
                        if (children->get(i) != dynamic_cast<JObject*>(refChild)){
                            continue;
                        }
                        child->setParentNode (this, i);
                        JSystem::arraycopy(children, i, children, i + 1, length - i);
                        children->set(i, child);
                        length++;
                        mutated();
                        return newChild;
                    }
                    throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                }

                JNode* JParentNode::replaceChild(JNode* newChild, JNode* refChild){
                    JNodeBase* child=null;
                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    if (newChild == null || refChild == null){
                        throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                    if (children == null){
                        throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                    }
                    child = checkDocument(newChild);
                    if (newChild->getNodeType() == DOCUMENT_FRAGMENT_NODE) {
                        consumeFragment(newChild, refChild);
                        return removeChild (refChild);
                    }
                    checkNotAncestor(newChild);
                    checkChildType(newChild->getNodeType ());

                    for (jint i = 0; i < length; i++) {
                        if (children->get(i) == dynamic_cast<JObject*>(newChild)) {
                            removeChild(newChild);
                            break;
                        }
                    }

                    for (jint i = 0; i < length; i++) {
                        if (children->get(i) != dynamic_cast<JObject*>(refChild)){
                            continue;
                        }
                        child->setParentNode(this, i);
                        children->set(i, child);
                        (dynamic_cast<JNodeBase*>(refChild))->setParentNode(null, -1);
                        mutated();
                        return refChild;
                    }
                    throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                }

                JNode* JParentNode::removeChild(JNode* oldChild){
                    JNodeBase* child=null;
                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    if (!(dynamic_cast<JObject*>(oldChild)->isInstanceOf(JNodeBase::getClazz()))){
                        throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                    }
                    child = dynamic_cast<JNodeBase*>(oldChild);
                    for (jint i = 0; i < length; i++) {
                        if (children->get(i) != dynamic_cast<JObject*>(child)){
                            continue;
                        }
                        if ((i + 1) != length){
                            JSystem::arraycopy(children, i + 1, children, i,(length - 1) - i);
                        }
                        length--;
                        children->set(length, null);
                        child->setParentNode(null, -1);
                        mutated();
                        return oldChild;
                    }
                    throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                }

                JNodeList* JParentNode::getElementsByTagName(JString* tagname){
                    if ((new JString("*"))->equals(tagname)){
                        tagname = null;
                    }
                    return new JTagList(this,tagname); 
                }

                JNodeList* JParentNode::getElementsByTagNameNS(JString* namespaceURI,JString* localName){
                    if ((new JString("*"))->equals(namespaceURI)) {
                        namespaceURI = null;
                    }
                    if ((new JString("*"))->equals(localName)) {
                        localName = null;
                    }
                    return new JTagListNS(this,namespaceURI, localName); 
                }

                jint JParentNode::getIndexOf(JNode* maybeChild){
                    for (jint i = 0; i < length; i++){
                        if (children->get(i) == dynamic_cast<JObject*>(maybeChild)){
                            return i;
                        }
                    }
                    return -1;
                }

                void JParentNode::normalize(){
                    jbool preserve = false;
                    jbool knowPreserve = false;

                    if (readonly) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }

                    for (jint i = 0; true; i++) {
                        JNode* node=item(i);
                        if (node == null) {
                            break;
                        }
                        switch(node->getNodeType()) {
                            case ELEMENT_NODE:
                                (dynamic_cast<JElement*>(node))->normalize();
                                continue;

                            case TEXT_NODE: {
                                JNode* node2 = item(i + 1);
                                if (node2 == null || node2->getNodeType() != TEXT_NODE) {
                                    continue;
                                }
                                (dynamic_cast<JTextNode*>(node))->joinNextText();
                                i--;
                                continue;

                            }

                            default:
                                continue;
                        }
                    }
                }

                jint JParentNode::removeWhiteSpaces(JPrimitiveCharArray* buf){
                    jint current = 0;
                    jint j = 0;

                    while (j < buf->size()) {
                        jbool sawSpace = false;
                        jchar c = buf->getChar(j++);

                        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                            c = ' ';
                            sawSpace = true;
                        }
                        buf->setChar(current++, c);
                        if (sawSpace) {
                            while (j < buf->size()) {
                                c = buf->getChar(j);
                                if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                                    j++;
                                    continue;

                                } else {
                                    break;
                                }
                            }
                        }
                    }
                    return current;
                }

                JParentNode::~JParentNode(){
                }
            }
        }
    }
}
