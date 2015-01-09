#include "jcpp/xml/internal/tree/JElementNode2.h"
#include "jcpp/xml/internal/tree/JTextNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/xml/internal/tree/JAttributeNode.h"
#include "jcpp/xml/internal/tree/JAttributeNode1.h"
#include "jcpp/xml/internal/util/JXmlNames.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/io/JCharArrayWriter.h"
#include "org/w3c/dom/JDOMException.h"
#include "jcpp/lang/JException.h"

using namespace jcpp::xml::internal::util;
using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JPrimitiveCharArray* JElementNode2::tagStart = null;

                JPrimitiveCharArray* JElementNode2::getTagStart(){
                    if (tagStart==null){
                        tagStart = new JPrimitiveCharArray(2);
                        tagStart->setChar(0,'<');
                        tagStart->setChar(1,'/');
                    }   
                    return tagStart;
                }

                JPrimitiveCharArray* JElementNode2::tagEnd = null;

                JPrimitiveCharArray* JElementNode2::getTagEnd(){
                    if (tagEnd==null){
                        tagEnd = new JPrimitiveCharArray(3);
                        tagEnd->setChar(0,' ');
                        tagEnd->setChar(1,'/');
                        tagEnd->setChar(2,'>');
                    }   
                    return tagEnd;
                }

                JElementNode2::JElementNode2(JClass* _class,JString* namespaceURI,JString* qName):JNamespacedNode(_class,namespaceURI,qName){
                    attributes=null;
                    idAttributeName=null;
                    userObject=null;
                }

                JElementNode2::JElementNode2(JString* namespaceURI,JString* qName):JNamespacedNode(getClazz(),namespaceURI,qName){
                    attributes=null;
                    idAttributeName=null;
                    userObject=null;
                }

                JElementNode2* JElementNode2::makeClone(){
                    JElementNode2* retval = new JElementNode2(namespaceURI, qName);
                    if (attributes != null) {
                        retval->attributes = new JAttributeSet(attributes, true);
                        retval->attributes->setOwnerElement(retval);
                    }
                    retval->idAttributeName = idAttributeName;
                    retval->userObject = userObject;
                    retval->ownerDocument = ownerDocument;
                    return retval;
                }

                JElementNode2* JElementNode2::createCopyForImportNode(jbool deep){
                    JElementNode2* retval = new JElementNode2(namespaceURI, qName);
                    if (attributes != null) {
                        retval->attributes = new JAttributeSet(attributes);
                        retval->attributes->setOwnerElement(retval);
                    }
                    retval->userObject = userObject;

                    if (deep) {
                        retval->ownerDocument = ownerDocument;

                        for (jint i = 0; true; i++) {
                            JNode* node = item(i);
                            if (node == null) {
                                break;
                            }
                            if (dynamic_cast<JObject*>(node)->isInstanceOf(JElementNode2::getClazz())) {
                                retval->appendChild(dynamic_cast<JElementNode2*>(node)->createCopyForImportNode(true));
                            } else {
                                retval->appendChild(node->cloneNode(true));
                            }
                        }
                    }
                    return retval;
                }

                void JElementNode2::checkArguments(JString* namespaceURI, JString* qualifiedName){
                    if (qualifiedName == null) {
                        throw new JDOMException(JDOMException::NAMESPACE_ERR);
                    }
                    jint first = qualifiedName->indexOf(':');

                    if (first <= 0) {
                        if (!JXmlNames::isUnqualifiedName(qualifiedName)) {
                            throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                        }
                        return;
                    }

                    jint last = qualifiedName->lastIndexOf(':');
                    if (last != first) {
                        throw new JDOMException(JDOMException::NAMESPACE_ERR);
                    }
                
                    JString* prefix = qualifiedName->substring(0, first);
                    JString* localName = qualifiedName->substring(first + 1);
                    if (!JXmlNames::isUnqualifiedName(prefix) || !JXmlNames::isUnqualifiedName(localName)) {
                        throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                    }

                    if (namespaceURI == null || (prefix->equals(new JString("xml")) && !JXmlNames::SPEC_XML_URI->equals(namespaceURI))) {
                        throw new JDOMException(JDOMException::NAMESPACE_ERR);
                    }
                }

                void JElementNode2::trimToSize(){
                    JNamespacedNode::trimToSize();
                    if (attributes != null){
                        attributes->trimToSize();
                    }
                }

                void JElementNode2::setAttributes(JAttributeSet* a){
                    JAttributeSet* oldAtts = attributes;
                    if (oldAtts != null && oldAtts->isReadonly()) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    if (a != null) {
                        a->setOwnerElement(this);
                    }
                    attributes = a;
                    if (oldAtts != null) {
                        oldAtts->setOwnerElement(null);
                    }
                }

                void JElementNode2::checkChildType(jint type){
                    switch (type) {
                        case ELEMENT_NODE:
                        case TEXT_NODE:
                        case COMMENT_NODE:
                        case PROCESSING_INSTRUCTION_NODE:
                        case CDATA_SECTION_NODE:
                        case ENTITY_REFERENCE_NODE:
                            return;
                        default:
                            throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                }

                void JElementNode2::setReadonly(jbool deep){
                    if (attributes != null){
                        attributes->setReadonly();
                    }
                    JNamespacedNode::setReadonly(deep);
                }

                JNamedNodeMap* JElementNode2::getAttributes(){
                    if (attributes == null){
                        attributes = new JAttributeSet(this);
                    }
                    return attributes;
                }

                jbool JElementNode2::hasAttributes(){
                    return attributes != null;
                }

                JString* JElementNode2::toString(){
                    try {
                        JCharArrayWriter* out = new JCharArrayWriter();
                        JXmlWriteContext* x = new JXmlWriteContext(out);
                        writeXml(x);
                        return out->toString ();
                    } catch(JException* e) {
                        return JNamespacedNode::toString();
                    }
                }

                void JElementNode2::writeXml(JXmlWriteContext* context){
                    JWriter*  out = context->getWriter();
                    if (qName == null){
                       throw new JIllegalStateException(new JString("null name"));
                    }   
                    out->write(getTagStart(), 0, 1);
                    out->write(qName);
                    if (attributes != null){
                        attributes->writeXml(context);
                    }

                    if (!hasChildNodes ()){
                        out->write(getTagEnd(), 0, 3);
                    }else  {
                        out->write(getTagEnd(), 2, 1);
                        writeChildrenXml(context);
                        out->write(getTagStart(), 0, 2);
                        out->write(qName);
                        out->write(getTagEnd(), 2, 1);
                    }
                }

                void JElementNode2::setIdAttributeName(JString* attName){
                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    idAttributeName = attName;
                }

                JString* JElementNode2::getIdAttributeName(){
                    return idAttributeName;
                }

                void JElementNode2::setUserObject(JObject* userObject){
                    this->userObject = userObject;
                }

                JObject* JElementNode2::getUserObject(){
                    return userObject;
                }

                jshort JElementNode2::getNodeType(){
                    return ELEMENT_NODE;
                }

                JString* JElementNode2::getTagName(){
                    return qName;
                }

                jbool JElementNode2::hasAttribute(JString* name){
                    return getAttributeNode(name) != null;
                }

                jbool JElementNode2::hasAttributeNS(JString* namespaceURI, JString* localName){
                    return getAttributeNodeNS(namespaceURI, localName) != null;
                }

                JString* JElementNode2::getAttribute(JString* name){
                    return (attributes == null) ? new JString("") : attributes->getValue(name);
                }

                JString* JElementNode2::getAttributeNS(JString* namespaceURI, JString* localName){
                    if (attributes == null) {
                        return new JString("");
                    }
                    JAttr* attr = getAttributeNodeNS(namespaceURI, localName);
                    if (attr == null) {
                        return new JString("");
                    }
                    return attr->getValue();
                }

                JAttr* JElementNode2::getAttributeNodeNS(JString* namespaceURI, JString* localName){
                    if (localName == null) {
                        return null;
                    }
                    if (attributes == null) {
                        return null;
                    }
                    for (jint i = 0; ; i++) {
                        JAttributeNode* attr = dynamic_cast<JAttributeNode*>(attributes->item(i));
                        if (attr == null) {
                            return null;
                        }
                        if (localName->equals(attr->getLocalName())
                            && (attr->getNamespaceURI() == namespaceURI || attr->getNamespaceURI()->equals(namespaceURI))) {
                            return attr;
                        }
                    }
                }

                void JElementNode2::setAttribute(JString* name, JString* value){
                    JNodeBase* att=null;
                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    if (!JXmlNames::isName(name)) {
                        throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                    }

                    if (attributes == null){
                        attributes = new JAttributeSet(this);
                    }
                    if ((att = dynamic_cast<JNodeBase*>(attributes->getNamedItem(name))) != null){
                        att->setNodeValue(value);
                    
                    }else {
                        att = new JAttributeNode1(name, value, true, null);
                        att->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                        attributes->setNamedItem (att);
                    }
                }

                void JElementNode2::setAttributeNS(JString* namespaceURI, JString* qualifiedName, JString* value){
                    JAttributeNode::checkArguments(namespaceURI, qualifiedName);

                    JAttr* attr = getAttributeNodeNS(namespaceURI,JXmlNames::getLocalPart(qualifiedName));
                    if (attr == null) {
                        JAttributeNode* newAttr = new JAttributeNode(namespaceURI,qualifiedName, value,true, null);
                        newAttr->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                        setAttributeNodeNS(newAttr);
                    } else {
                        attr->setValue(value);
                        attr->setPrefix(JXmlNames::getPrefix(qualifiedName));
                    }
                }

                JAttr* JElementNode2::setAttributeNodeNS(JAttr* newAttr){
                    if (readonly) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    if (newAttr->getOwnerDocument() != getOwnerDocument()) {
                        throw new JDOMException(JDOMException::WRONG_DOCUMENT_ERR);
                    }
                    if (attributes == null) {
                        attributes = new JAttributeSet(this);
                    }
                    return dynamic_cast<JAttr*>(attributes->setNamedItemNS(newAttr));
                }

                void JElementNode2::removeAttribute(JString* name){
                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    if (attributes == null) {
                        return;
                    }
                    try {
                        attributes->removeNamedItem(name);
                    } catch(JDOMException* x) {
                        if (x->code->get() != JDOMException::NOT_FOUND_ERR) {
                            throw x;
                        }
                    }
                }

                void JElementNode2::removeAttributeNS(JString* namespaceURI, JString* localName){
                    if (readonly) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    try {
                        attributes->removeNamedItemNS(namespaceURI, localName);
                    } catch (JDOMException* x) {
                        if (x->code->get() != JDOMException::NOT_FOUND_ERR) {
                            throw x;
                        }
                    }
                }

                JAttr* JElementNode2::getAttributeNode(JString* name){
                    if (attributes != null){
                        return dynamic_cast<JAttr*>(attributes->getNamedItem(name));
                    }else{
                        return null;
                    }
                }

                JAttr* JElementNode2::setAttributeNode(JAttr* newAttr){
                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    if (!(dynamic_cast<JObject*>(newAttr)->isInstanceOf(JAttributeNode::getClazz()))){
                        throw new JDOMException(JDOMException::WRONG_DOCUMENT_ERR);
                    }

                    if (attributes == null) {
                        attributes = new JAttributeSet(this);
                    }

                    return dynamic_cast<JAttr*>(attributes->setNamedItem(newAttr));
                }

                JAttr* JElementNode2::removeAttributeNode(JAttr* oldAttr){
                    if (isReadonly()){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }

                    JAttr* attr = getAttributeNode(oldAttr->getNodeName());
                    if (attr == null){
                        throw new JDOMException(JDOMException::NOT_FOUND_ERR);
                    }
                    removeAttribute(attr->getNodeName());
                    return attr;
                }

                JNode* JElementNode2::cloneNode(jbool deep){
                    JElementNode2* retval = makeClone();
                    if (deep) {
                        for (jint i = 0; true; i++) {
                            JNode* node = item(i);
                            if (node == null){
                                break;
                            }
                            retval->appendChild(node->cloneNode(true));
                        }
                    }
                    return retval;
                }

                void JElementNode2::write(JWriter* out){
                    writeXml(new JXmlWriteContext(out));
                }

                JNodeList* JElementNode2::getElementsByTagNameNS(JString* namespaceURI,JString* localName){
                    throw new JException(new JString("TODO not implemented"));
                }

                JTypeInfo* JElementNode2::getSchemaTypeInfo(){
                    throw new JException(new JString("TODO not implemented"));
                }

                void JElementNode2::setIdAttribute(JString* name,jbool isId){
                    throw new JException(new JString("TODO not implemented"));
                }

                void JElementNode2::setIdAttributeNS(JString* namespaceURI,JString* localName,jbool isId){
                    throw new JException(new JString("TODO not implemented"));
                }

                void JElementNode2::setIdAttributeNode(JAttr* idAttr,jbool isId){
                    throw new JException(new JString("TODO not implemented"));
                }

                JNodeList* JElementNode2::getElementsByTagName(JString* name){
                    throw new JException(new JString("TODO not implemented"));
                }

                JElementNode2::~JElementNode2(){
                }
            }
        }
    }
}
