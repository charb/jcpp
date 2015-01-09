#include "jcpp/xml/internal/tree/JAttributeSet.h"
#include "jcpp/xml/internal/tree/JTextNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/xml/internal/util/JXmlNames.h"
#include "jcpp/xml/internal/tree/JAttributeNode.h"
#include "jcpp/xml/internal/tree/JAttributeNode1.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"
#include "jcpp/io/JCharArrayWriter.h"
#include "jcpp/xml/internal/parser/JAttributesEx.h"

using namespace jcpp::xml::internal::util;
using namespace jcpp::xml::internal::parser;
using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JAttributeSet::JAttributeSet():JObject(getClazz()){
                    readonly=false;
                    list=null;
                    ownerElement=null;
                }

                JAttributeSet::JAttributeSet(JElement* ownerElement):JObject(getClazz()){
                    readonly=false;
                    list=new JVector(5);
                    this->ownerElement=ownerElement;
                }

                JAttributeSet::JAttributeSet(JAttributeSet* original, jbool deep):JObject(getClazz()){
                    readonly=false;
                    ownerElement=null;
                    
                    jint size = original->getLength();
                    list = new JVector(size);
                    for (jint i = 0; i < size; i++) {
                        JNode* node = original->item(i);

                        if (!(dynamic_cast<JObject*>(node)->isInstanceOf(JAttributeNode::getClazz()))){
                            throw new JIllegalArgumentException();
                        }

                        JAttributeNode* attr = dynamic_cast<JAttributeNode*>(node);
                        node = attr->cloneAttributeNode(deep);
                        list->addElement(dynamic_cast<JObject*>(node));
                    }
                }

                JAttributeSet::JAttributeSet(JAttributeSet* original):JObject(getClazz()){
                    readonly=false;
                    ownerElement=null;

                    jint size = original->getLength();
                    list = new JVector(size);

                    for (jint i = 0; i < size; i++) {
                        JNode* node = original->item(i);

                        if (!(dynamic_cast<JObject*>(node)->isInstanceOf(JAttributeNode::getClazz()))) {
                            throw new JIllegalArgumentException();
                        }

                        JAttributeNode* attr = dynamic_cast<JAttributeNode*>(node);
                        if (attr->getSpecified()) {
                            node = attr->cloneAttributeNode(true);
                            list->addElement(dynamic_cast<JObject*>(node));
                        }
                    }
                    list->trimToSize();
                }

                JAttributeSet* JAttributeSet::createAttributeSet2(JAttributes* source){
                    JAttributeSet* retval = new JAttributeSet();
                    jint len = source->getLength();
                    JAttributesEx* ex = null;
                    retval->list = new JVector(len);
                    if (dynamic_cast<JObject*>(source)->isInstanceOf(JAttributesEx::getClazz())) {
                        ex = dynamic_cast<JAttributesEx*>(source);
                    }

                    for (jint i = 0; i < len; i++) {
                        JString* uri=null;
                        JString* qName = source->getQName(i);
                        if ((new JString("xmlns"))->equals(qName) || (new JString("xmlns"))->equals(JXmlNames::getPrefix(qName))) {
                            uri = JXmlNames::SPEC_XMLNS_URI;

                        } else {
                            uri = source->getURI(i);
                            if ((new JString(""))->equals(uri)) {
                                uri = null;
                            }
                        }

                        JAttributeNode* attrNode = new JAttributeNode(uri, qName,source->getValue(i), ex == null? true: ex->isSpecified(i), ex == null? null : ex->getDefault(i));
                        retval->list->addElement(attrNode);
                    }
                    return retval;
                }

                JAttributeSet* JAttributeSet::createAttributeSet1(JAttributes* source){
                    JAttributeSet* retval = new JAttributeSet();
                    jint len = source->getLength();
                    JAttributesEx* ex = null;

                    retval->list = new JVector(len);
                    if (dynamic_cast<JObject*>(source)->isInstanceOf(JAttributesEx::getClazz())) {
                        ex = dynamic_cast<JAttributesEx*>(source);
                    }

                    for (jint i = 0; i < len; i++) {
                        JAttributeNode1* attrNode1 = new JAttributeNode1(source->getQName(i),source->getValue(i), ex == null ? true : ex->isSpecified(i), ex == null ? null : ex->getDefault(i));
                        retval->list->addElement(attrNode1);
                    }
                    return retval;
                }

                void JAttributeSet::trimToSize(){
                    list->trimToSize();
                }

                void JAttributeSet::setReadonly(){
                    readonly = true;
                    for (jint i = 0; i < list->size(); i++){
                        (dynamic_cast<JAttributeNode*>(list->elementAt(i)))->setReadonly(true);
                    }
                }

                jbool JAttributeSet::isReadonly(){
                    if (readonly){
                        return true;
                    }
                    for (jint i = 0; i < list->size(); i++) {
                        if ((dynamic_cast<JAttributeNode*>(list->elementAt(i)))->isReadonly()) {
                            return true; 
                        }
                    }
                    return false;
                }

                void JAttributeSet::setOwnerElement(JElement* e){
                    if (e != null && ownerElement != null) {
                        throw new JIllegalStateException();
                    }
                    ownerElement = e;
                    jint length = list->size();

                    for (jint i = 0; i < length; i++) {
                        JAttributeNode* node= dynamic_cast<JAttributeNode*>(list->elementAt(i));
                        node->setOwnerElement(null);
                        node->setOwnerElement(e);
                    }
                }

                JString* JAttributeSet::getValue(JString* name){
                    JAttr* attr = dynamic_cast<JAttr*>(getNamedItem(name));
                    if (attr == null){
                        return new JString("");
                    }else{
                        return attr->getValue();
                    }
                }

                JNode* JAttributeSet::getNamedItem(JString* name){
                    jint length = list->size();
                    JNode* value=null;
                    for (jint i = 0; i < length; i++) {
                        value =item(i);
                        if (value->getNodeName()->equals(name)){
                            return value;
                        }
                    }
                    return null;
                }

                JNode* JAttributeSet::getNamedItemNS(JString* namespaceURI, JString* localName){
                    if (localName == null) {
                        return null;
                    }

                    for (jint i = 0; i < list->size(); i++) {
                        JNode* value = item(i);
                        JString* iLocalName = value->getLocalName();
                        if (localName->equals(iLocalName)) {
                            JString* iNamespaceURI = value->getNamespaceURI();
                            if (namespaceURI == iNamespaceURI || (namespaceURI != null && namespaceURI->equals(iNamespaceURI))) {
                                return value;
                            }
                        }
                    }
                    return null;
                }

                jint JAttributeSet::getLength(){
                    return list->size();
                }

                JNode* JAttributeSet::item(jint index){
                    if (index < 0 || index >= list->size()){
                        return null;
                    }
                    return dynamic_cast<JNode*>(list->elementAt(index));
                }

                JNode* JAttributeSet::removeNamedItem(JString* name){
                     if (readonly) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    for (jint i = 0; i < list->size(); i++) {
                        JNode* value = dynamic_cast<JNode*>(list->elementAt(i));
                        if (value->getNodeName()->equals(name)) {
                            list->removeElementAt(i);
                            JAttributeNode* attr = dynamic_cast<JAttributeNode*>(value);
                            JString* defaultValue = attr->getDefaultValue();
                            if (defaultValue != null) {
                                JAttributeNode* newAttr = attr->cloneAttributeNode(true);
                                newAttr->setOwnerElement(attr->getOwnerElement());
                                newAttr->setValue(defaultValue);
                                newAttr->setSpecified(false);
                                list->addElement(newAttr);
                            }

                            attr->setOwnerElement(null);
                            return attr;
                        }
                    }
                    throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                }

                JNode* JAttributeSet::removeNamedItemNS(JString* namespaceURI, JString* localName){
                    if (readonly) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }

                    if (localName == null) {
                        throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                    }

                    for (jint i = 0; i < list->size(); i++) {
                        JNode* value = dynamic_cast<JNode*>(list->elementAt(i));
                        JString* iLocalName = value->getLocalName();
                        if (localName->equals(iLocalName)) {
                            JString* iNamespaceURI = value->getNamespaceURI();
                            if (namespaceURI == iNamespaceURI || (namespaceURI != null && namespaceURI->equals(iNamespaceURI))) {
                                list->removeElementAt(i);
                                JAttributeNode* attr = dynamic_cast<JAttributeNode*>(value);

                                JString* defaultValue = attr->getDefaultValue();
                                if (defaultValue != null) {
                                    JAttributeNode* newAttr = attr->cloneAttributeNode(true);
                                    newAttr->setOwnerElement(attr->getOwnerElement());
                                    newAttr->setValue(defaultValue);
                                    newAttr->setSpecified(false);
                                    list->addElement(newAttr);
                                }
                                attr->setOwnerElement(null);
                                return attr;
                            }
                        }
                    }
                    throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                }

                JNode* JAttributeSet::setNamedItem(JNode* value){
                    if (readonly) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    if (!(dynamic_cast<JObject*>(value)->isInstanceOf(JAttributeNode::getClazz())) || value->getOwnerDocument() != ownerElement->getOwnerDocument()) {
                        throw new JDOMException(JDOMException::WRONG_DOCUMENT_ERR);
                    }

                    JAttributeNode* att = dynamic_cast<JAttributeNode*>(value);
                    if (att->getOwnerElement() != null) {
                        throw new JDOMException(JDOMException::INUSE_ATTRIBUTE_ERR);
                    }

                    jint length = list->size();
                    JAttributeNode* oldAtt=null;
                    for (jint i = 0; i < length; i++) {
                        oldAtt = dynamic_cast<JAttributeNode*>(item(i));
                        if (oldAtt->getNodeName()->equals(value->getNodeName())) {
                            if (oldAtt->isReadonly()) {
                                throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                            }
                            att->setOwnerElement(ownerElement);
                            list->setElementAt(att, i);
                            oldAtt->setOwnerElement(null);
                            return oldAtt;
                        }
                    }
                    att->setOwnerElement(ownerElement);
                    list->addElement(dynamic_cast<JObject*>(value));
                    return null;
                }

                JNode* JAttributeSet::setNamedItemNS(JNode* arg){
                    if (readonly) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }

                    if (!(dynamic_cast<JObject*>(arg)->isInstanceOf(JAttributeNode::getClazz())) || arg->getOwnerDocument() != ownerElement->getOwnerDocument()) {
                        throw new JDOMException(JDOMException::WRONG_DOCUMENT_ERR);
                    }

                    JAttributeNode* attr = dynamic_cast<JAttributeNode*>(arg);
                    if (attr->getOwnerElement() != null) {
                        throw new JDOMException(JDOMException::INUSE_ATTRIBUTE_ERR);
                    }

                    JString* localName = attr->getLocalName();
                    JString* namespaceURI = attr->getNamespaceURI();

                    jint length = list->size();
                    for (jint i = 0; i < length; i++) {
                        JAttributeNode* oldNode = dynamic_cast<JAttributeNode*>(item(i));
                        JString* iLocalName = oldNode->getLocalName();
                        JString* iNamespaceURI = oldNode->getNamespaceURI();
                        
                        if ((localName == iLocalName || (localName != null && localName->equals(iLocalName)))
                            && (namespaceURI == iNamespaceURI || (namespaceURI != null && namespaceURI->equals(iNamespaceURI)))) {
                            if (oldNode->isReadonly()) {
                                throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                            }
                            attr->setOwnerElement(ownerElement);
                            list->setElementAt(attr, i);
                            oldNode->setOwnerElement(null);
                            return oldNode;
                        }
                    }

                    attr->setOwnerElement(ownerElement);
                    list->addElement(attr);
                    return null;
                }

                void JAttributeSet::writeXml(JXmlWriteContext* context){
                    JWriter* out = context->getWriter();
                    jint length = list->size();
                    JAttributeNode* tmp=null;

                    for (jint i = 0; i < length; i++) {
                        tmp = dynamic_cast<JAttributeNode*>(list->elementAt(i));
                        if (tmp->getSpecified()) {
                            out->write(' ');
                            tmp->writeXml(context);
                        }
                    }
                }

                void JAttributeSet::writeChildrenXml(JXmlWriteContext* context){
                }

                JString* JAttributeSet::toString(){
                    try {
                        JCharArrayWriter* w = new JCharArrayWriter();
                        JXmlWriteContext* x = new JXmlWriteContext(w);
                        writeXml(x);
                        return w->toString();

                    } catch (JIOException* e) {
                        return JObject::toString();
                    }
                }

                JAttributeSet::~JAttributeSet(){
                }
            }
        }
    }
}
