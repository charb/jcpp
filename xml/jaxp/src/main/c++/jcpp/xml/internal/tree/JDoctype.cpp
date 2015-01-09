#include "jcpp/xml/internal/tree/JDoctype.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"
#include "jcpp/lang/JException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JDoctype::JDoctype(JString* pub, JString* sys, JString* subset):JNodeBase(getClazz()){
                    publicId=pub;
                    systemId=sys;
                    internalSubset=subset;
                    name=null;
                    entities=null;
                    notations=null;
                }

                JDoctype::JDoctype(JString* name, JString* publicId, JString* systemId,JString* internalSubset):JNodeBase(getClazz()){
                    this->name = name;
                    this->publicId = publicId;
                    this->systemId = systemId;
                    this->internalSubset = internalSubset;
                    entities = new JNodemap();
                    notations = new JNodemap();
                }

                JDoctype::JNotationNode::JNotationNode(JString* name, JString* pub, JString* sys):JNodeBase(getClazz()){
                    notation = name;
                    publicId = pub;
                    systemId = sys;
                }

                JString* JDoctype::JNotationNode::getPublicId(){
                    return publicId;
                }

                JString* JDoctype::JNotationNode::getSystemId(){
                    return systemId;
                }

                jshort JDoctype::JNotationNode::getNodeType(){
                    return NOTATION_NODE;
                }

                JString* JDoctype::JNotationNode::getNodeName(){
                    return notation;
                }

                JNode* JDoctype::JNotationNode::cloneNode(jbool ignored){
                    JNotationNode* retval= new JNotationNode (notation, publicId, systemId);
                    retval->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    return retval;
                }

                void JDoctype::JNotationNode::writeXml(JXmlWriteContext* context){
                    JWriter* out = context->getWriter();
                    out->write(new JString("<!NOTATION "));
                    out->write(notation);
                    if (publicId != null) {
                        out->write(new JString(" PUBLIC '"));
                        out->write(publicId);
                        if (systemId != null) {
                            out->write(new JString("' '"));
                            out->write(systemId);
                        }
                    } else {
                        out->write(new JString(" SYSTEM '"));
                        out->write(systemId);
                    }
                    out->write(new JString("'>"));
                }

                JDoctype::JNotationNode::~JNotationNode(){
                }

                JDoctype::JEntityNode::JEntityNode(JString* name, JString* pub, JString* sys, JString* snot):JNodeBase(getClazz()){
                    entityName = name;
                    publicId = pub;
                    systemId = sys;
                    notation = snot;
                    value=null;
                }

                JDoctype::JEntityNode::JEntityNode(JString* name, JString* value):JNodeBase(getClazz()){
                    entityName = name;
                    this->value=null;
                    publicId = null;
                    systemId = null;
                    notation = null;
                }

                JString* JDoctype::JEntityNode::getNodeName(){
                    return entityName;
                }

                jshort JDoctype::JEntityNode::getNodeType(){
                    return ENTITY_NODE;
                }

                JString* JDoctype::JEntityNode::getPublicId(){
                    return publicId;
                }

                JString* JDoctype::JEntityNode::getSystemId(){
                    return systemId;
                }

                JString* JDoctype::JEntityNode::getNotationName(){
                    return notation;
                }

                JString* JDoctype::JEntityNode::getInputEncoding(){
                    throw new JException(new JString("TODO not implemented"));
                }

                JString* JDoctype::JEntityNode::getXmlEncoding(){
                    throw new JException(new JString("TODO not implemented"));
                }

                JString* JDoctype::JEntityNode::getXmlVersion(){
                    throw new JException(new JString("TODO not implemented"));
                }

                JNode* JDoctype::JEntityNode::cloneNode(jbool ignored){
                    JEntityNode* retval= new JEntityNode(entityName, publicId, systemId,notation);
                    retval->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    return retval;
                }

                void JDoctype::JEntityNode::writeXml(JXmlWriteContext* context){
                    JWriter* out = context->getWriter();
                    out->write(new JString("<!ENTITY "));
                    out->write(entityName);

                    if (value == null) {
                        if (publicId != null) {
                            out->write(new JString(" PUBLIC '"));
                            out->write(publicId);
                            out->write(new JString("' '"));

                        } else{
                            out->write(new JString(" SYSTEM '"));
                        }
                        out->write(systemId);
                        out->write(new JString("'"));
                        if (notation != null) {
                            out->write(new JString(" NDATA "));
                            out->write(notation);
                        }
                    } else {
                        out->write(new JString(" \""));
                        jint length = value->length ();
                        for (jint i = 0; i < length; i++) {
                            jchar c = value->charAt (i);
                            if (c == '"'){
                                out->write(new JString("&quot;"));
                            }else{
                                out->write (c);
                            }
                        }
                        out->write('"');
                    }
                    out->write(new JString(">"));
                }

                JDoctype::JEntityNode::~JEntityNode(){
                }

                JDoctype::JNodemap::JNodemap():JObject(getClazz()){
                    readonly=false;
                    list=new JVector();
                }

                JNode* JDoctype::JNodemap::getNamedItem(JString* name){
                    jint length = list->size();
                    JNode* value=null;

                    for (jint i = 0; i < length; i++) {
                        value = item(i);
                        if (value->getNodeName()->equals(name)){
                            return value;
                        }
                    }
                    return null;
                }

                JNode* JDoctype::JNodemap::getNamedItemNS(JString* namespaceURI, JString* localName){
                    return null;
                }

                jint JDoctype::JNodemap::getLength(){
                    return list->size();
                }

                JNode* JDoctype::JNodemap::item(jint index){
                    if (index < 0 || index >= list->size()){
                        return null;
                    }
                    return dynamic_cast<JNode*>(list->elementAt(index));
                }

                JNode* JDoctype::JNodemap::removeNamedItem(JString* name){
                    throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                }

                JNode* JDoctype::JNodemap::removeNamedItemNS(JString* namespaceURI, JString* localName){
                    throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                }

                JNode* JDoctype::JNodemap::setNamedItem(JNode* item){
                    if (readonly){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    list->addElement(dynamic_cast<JObject*>(item));
                    return null;
                }

                JNode* JDoctype::JNodemap::setNamedItemNS(JNode* arg){
                    if (readonly) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    list->addElement(dynamic_cast<JObject*>(arg));
                    return null;
                }

                JDoctype::JNodemap::~JNodemap(){
                }

                void JDoctype::setPrintInfo(JString* pub, JString* sys, JString* subset){
                    publicId = pub;
                    systemId = sys;
                    internalSubset = subset;
                }

                void JDoctype::writeXml(JXmlWriteContext* context){
                    JWriter*  out = context->getWriter();
                    JElement* root = getOwnerDocument()->getDocumentElement();

                    out->write(new JString("<!DOCTYPE "));
                    out->write(root == null ? new JString("UNKNOWN-ROOT") : root->getNodeName());

                    if (systemId != null) {
                        if (publicId != null) {
                            out->write(new JString(" PUBLIC '"));
                            out->write(publicId);
                            out->write(new JString("' '"));
                        } else{
                            out->write(new JString(" SYSTEM '"));
                        }
                        out->write(systemId);
                        out->write(new JString("'"));
                    }
                    if (internalSubset != null) {
                        out->write(JSystem::lineSeparator());
                        out->write(new JString("["));
                        out->write(internalSubset);
                        out->write(new JString("]"));
                    }
                    out->write(new JString(">"));
                    out->write(JSystem::lineSeparator());
                }

                jshort JDoctype::getNodeType(){
                    return DOCUMENT_TYPE_NODE;
                }

                JString* JDoctype::getName(){
                    return name;
                }

                JString* JDoctype::getNodeName(){
                    return name;
                }

                JNode* JDoctype::cloneNode(jbool deep){
                    JDoctype* retval = new JDoctype(name, publicId, systemId, internalSubset);
                    retval->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    return retval;
                }

                JNamedNodeMap* JDoctype::getEntities(){
                    return entities;
                }

                JNamedNodeMap* JDoctype::getNotations(){
                    return notations;
                }

                JString* JDoctype::getPublicId(){
                    return publicId;
                }

                JString* JDoctype::getSystemId(){
                    return systemId;
                }

                JString* JDoctype::getInternalSubset(){
                    return internalSubset;
                }

                void JDoctype::setOwnerDocument(JXmlDocument* doc){
                    JNodeBase::setOwnerDocument (doc);
                    if (entities != null){
                        for (jint i = 0; entities->item(i) != null; i++){
                            (dynamic_cast<JNodeBase*>(entities->item(i)))->setOwnerDocument(doc);
                        }
                    }
                    if (notations != null){
                        for (jint i = 0; notations->item(i) != null; i++){
                            (dynamic_cast<JNodeBase*>(notations->item(i)))->setOwnerDocument(doc);
                        }
                    }
                }

                void JDoctype::addNotation(JString* name, JString* pub, JString* sys){
                    JNotationNode* node = new JNotationNode(name, pub, sys);
                    node->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    notations->setNamedItem(node);
                }

                void JDoctype::addEntityNode(JString* name, JString* pub, JString* sys, JString* snot){
                    JEntityNode* node = new JEntityNode(name, pub, sys, snot);
                    node->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    entities->setNamedItem(node);
                }

                void JDoctype::addEntityNode(JString* name, JString* value){
                    if ((new JString("lt"))->equals(name) || (new JString("gt"))->equals(name)
                        || (new JString("apos"))->equals(name) || (new JString("quot"))->equals(name)
                        || (new JString("amp"))->equals(name)){
                        return;
                    }

                    JEntityNode* node = new JEntityNode(name, value);
                    node->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    entities->setNamedItem(node);
                }

                void JDoctype::setReadonly(){
                    entities->readonly = true;
                    notations->readonly = true;
                }

                JString* JDoctype::getNodeValue(){
                    return JNodeBase::getNodeValue();
                }

                void JDoctype::setNodeValue(JString* value){
                    JNodeBase::setNodeValue(value);
                }

                JNode* JDoctype::getParentNode(){
                    return JNodeBase::getParentNode();
                }

                JNodeList* JDoctype::getChildNodes(){
                    return JNodeBase::getChildNodes();
                }

                JNode* JDoctype::getFirstChild(){
                    return JNodeBase::getFirstChild();
                }

                JNode* JDoctype::getLastChild(){
                    return JNodeBase::getLastChild();
                }
    
                JNode* JDoctype::getPreviousSibling(){
                    return JNodeBase::getPreviousSibling();
                }

                JNode* JDoctype::getNextSibling(){
                    return JNodeBase::getNextSibling();
                }

                JNamedNodeMap* JDoctype::getAttributes(){
                    return JNodeBase::getAttributes();
                }

                JDocument* JDoctype::getOwnerDocument(){
                    return JNodeBase::getOwnerDocument();
                }

                JNode* JDoctype::insertBefore(JNode* newChild,JNode* refChild){
                    return JNodeBase::getOwnerDocument();
                }

                JNode* JDoctype::replaceChild(JNode* newChild,JNode* oldChild){
                    return JNodeBase::replaceChild(newChild,oldChild);
                }

                JNode* JDoctype::removeChild(JNode* oldChild){
                    return JNodeBase::removeChild(oldChild);
                }
    
                JNode* JDoctype::appendChild(JNode* newChild){
                    return JNodeBase::appendChild(newChild);
                }

                jbool JDoctype::hasChildNodes(){
                    return JNodeBase::hasChildNodes();
                }

                void JDoctype::normalize(){
                    JNodeBase::normalize();
                }

                jbool JDoctype::isSupported(JString* feature,JString* version){
                    return JNodeBase::isSupported(feature,version);
                }

                JString* JDoctype::getNamespaceURI(){
                    return JNodeBase::getNamespaceURI();
                }

                JString* JDoctype::getPrefix(){
                    return JNodeBase::getPrefix();
                }

                void JDoctype::setPrefix(JString* prefix){
                    JNodeBase::setPrefix(prefix);
                }

                JString* JDoctype::getLocalName(){
                    return JNodeBase::getLocalName();
                }

                jbool JDoctype::hasAttributes(){
                    return JNodeBase::hasAttributes();
                }

                JDoctype::~JDoctype(){
                }
            }
        }
    }
}
