#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/xml/internal/tree/JElementNode.h"
#include "jcpp/xml/internal/tree/JElementNode2.h"
#include "jcpp/xml/internal/tree/JXmlDocumentBuilder.h"
#include "jcpp/xml/internal/tree/JCDataNode.h"
#include "jcpp/xml/internal/tree/JAttributeNode1.h"
#include "jcpp/xml/internal/tree/JAttributeNode.h"
#include "jcpp/xml/internal/tree/JPINode.h"
#include "jcpp/xml/internal/util/JXmlNames.h"
#include "jcpp/xml/internal/tree/JDOMImplementationImpl.h"
#include "jcpp/xml/internal/tree/JCommentNode.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/io/JOutputStreamWriter.h"
#include "jcpp/lang/JException.h"
#include "org/xml/sax/helpers/JXMLReaderFactory.h"
#include "org/xml/sax/JXMLReader.h"
#include "org/w3c/dom/JDOMException.h"
#include "org/xml/sax/helpers/JDefaultHandler.h"

using namespace jcpp::io;
using namespace jcpp::xml::internal::util;
using namespace org::xml::sax;
using namespace org::xml::sax::helpers;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JXmlDocument::JXmlDocument(JClass* _class):JParentNode(_class){
                    systemId=null;
                    factory=null;
                    mutationCount=0;
                    replaceRootElement=false;
                }

                JXmlDocument::JXmlDocument():JParentNode(getClazz()){
                    systemId=null;
                    factory=null;
                    mutationCount=0;
                    replaceRootElement=false;
                }

                JXmlDocument::JDocFragNode::JDocFragNode():JParentNode(getClazz()){
                }

                void JXmlDocument::JDocFragNode::checkChildType(jint type){
                    switch (type) {
                        case ELEMENT_NODE:
                        case PROCESSING_INSTRUCTION_NODE:
                        case COMMENT_NODE:
                        case TEXT_NODE:
                        case CDATA_SECTION_NODE:
                        case ENTITY_REFERENCE_NODE:
                            return;
                        default:
                            throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                }

                void JXmlDocument::JDocFragNode::writeXml(JXmlWriteContext* context){
                    writeChildrenXml(context);
                }

                JNode* JXmlDocument::JDocFragNode::getParentNode(){
                    return null;
                }

                void JXmlDocument::JDocFragNode::setParentNode(JNode* p){
                    if (p != null){ 
                        throw new JIllegalArgumentException();
                    }
                }

                jshort JXmlDocument::JDocFragNode::getNodeType(){
                    return DOCUMENT_FRAGMENT_NODE;
                }

                JString* JXmlDocument::JDocFragNode::getNodeName(){
                    return new JString("#document-fragment");
                }

                JNode* JXmlDocument::JDocFragNode::cloneNode(jbool deep){
                    JDocFragNode* retval = new JDocFragNode();
                    (dynamic_cast<JNodeBase*>(retval))->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    if (deep) {
                        JNode* node=null;
                        for (jint i = 0; (node = item(i)) != null; i++) {
                            node = node->cloneNode(true);
                            retval->appendChild(node);
                        }
                    }
                    return retval;
                }

                JXmlDocument::JDocFragNode::~JDocFragNode(){
                }

                JXmlDocument::JEntityRefNode::JEntityRefNode(JString* name):JParentNode(getClazz()){
                    if (name == null){
                        throw new JIllegalArgumentException();
                    }
                    entity = name;
                }

                void JXmlDocument::JEntityRefNode::checkChildType(jint type){
                    switch (type) {
                        case ELEMENT_NODE:
                        case PROCESSING_INSTRUCTION_NODE:
                        case COMMENT_NODE:
                        case TEXT_NODE:
                        case CDATA_SECTION_NODE:
                        case ENTITY_REFERENCE_NODE:
                            return;
                        default:
                            throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                }

                void JXmlDocument::JEntityRefNode::writeXml(JXmlWriteContext* context){
                    if (!context->isEntityDeclared(entity)){
                        throw new JIOException();
                    }
                    JWriter* out = context->getWriter();
                    out->write('&');
                    out->write(entity);
                    out->write(';');
                }

                jshort JXmlDocument::JEntityRefNode::getNodeType(){
                    return ENTITY_REFERENCE_NODE;
                }

                JString* JXmlDocument::JEntityRefNode::getNodeName(){
                    return entity;
                }

                JNode* JXmlDocument::JEntityRefNode::cloneNode(jbool deep){
                    JEntityRefNode* retval = new JEntityRefNode(entity);
                    (dynamic_cast<JNodeBase*>(retval))->setOwnerDocument(dynamic_cast<JXmlDocument*>(getOwnerDocument()));
                    if (deep) {
                        JNode* node=null;
                        for (jint i = 0; (node = item(i)) != null; i++) {
                            node = node->cloneNode(true);
                            retval->appendChild(node);
                        }
                    }
                    return retval;
                }

                JXmlDocument::JEntityRefNode::~JEntityRefNode(){
                }

                JXmlDocument::JExtWriteContext::JExtWriteContext(JXmlDocument* xmlDocument,JWriter* out):JXmlWriteContext(getClazz(),out){
                    this->xmlDocument=xmlDocument;
                }
                
                JXmlDocument::JExtWriteContext::JExtWriteContext(JXmlDocument* xmlDocument,JWriter* out, jint level):JXmlWriteContext(getClazz(),out,level){
                    this->xmlDocument=xmlDocument;
                }

                jbool JXmlDocument::JExtWriteContext::isEntityDeclared(JString* name){
                    if (JXmlWriteContext::isEntityDeclared(name)){
                        return true;
                    }
                    JDocumentType* doctype = xmlDocument->getDoctype();
                    if (doctype == null){
                        return false;
                    }else{
                        return doctype->getEntities()->getNamedItem(name)!= null;
                    }
                }

                JXmlDocument::JExtWriteContext::~JExtWriteContext(){
                }

                JXmlDocument* JXmlDocument::createXmlDocument(JString* documentURI,jbool doValidate){
                    return createXmlDocument(new JInputSource(documentURI), doValidate);
                }

                JXmlDocument* JXmlDocument::createXmlDocument(JString* documentURI){
                    return createXmlDocument(new JInputSource(documentURI), false);
                }

                JXmlDocument* JXmlDocument::createXmlDocument(JInputStream* in,jbool doValidate){
                    return createXmlDocument(new JInputSource(in), doValidate);
                }

                // @Class(canonicalName="javax.xml.internal.tree.XmlDocument$1", simpleName="XmlDocument$1");
                class JDefaultHandlerImpl : public JDefaultHandler{
                public:
                    JDefaultHandlerImpl():JDefaultHandler(getClazz()){
                    }

                    static JClass* getClazz();

                    virtual void error(JSAXParseException* e){
                        throw e;
                    }

                    virtual ~JDefaultHandlerImpl(){
                    }
                };

                JXmlDocument* JXmlDocument::createXmlDocument(JInputSource* in,jbool doValidate){
                    JXMLReader* xmlReader = JXMLReaderFactory::createXMLReader();
                    JXmlDocumentBuilder* builder = new JXmlDocumentBuilder();
                    xmlReader->setContentHandler(builder);
                    xmlReader->setDTDHandler(builder);
                    if (doValidate) {
                        xmlReader->setErrorHandler(new JDefaultHandlerImpl());
                    }
                    builder->setDisableNamespaces(true);
                    xmlReader->parse(in);
                    return builder->getDocument();
                }

                void JXmlDocument::write(JOutputStream* out){
                    JWriter*  writer = new JOutputStreamWriter(out);
                    write(writer, null);
                }

                void JXmlDocument::write(JWriter* out){
                    write(out, null);
                }

                void JXmlDocument::write(JWriter* out, JString* encoding){
                    out->write(new JString("<?xml version=\"1.0\""));
                    if (encoding != null) {
                        out->write(new JString(" encoding=\""));
                        out->write(encoding);
                        out->write('\"');
                    }
                    out->write(new JString("?>"));
                    out->write(JSystem::lineSeparator());
                    out->write(JSystem::lineSeparator());

                    writeChildrenXml(createWriteContext(out, 0));
                    out->write(JSystem::lineSeparator());
                    out->flush();
                }

                JXmlWriteContext* JXmlDocument::createWriteContext(JWriter* out){
                    return new JExtWriteContext(this,out);
                }

                JXmlWriteContext* JXmlDocument::createWriteContext(JWriter* out, jint level){
                    return new JExtWriteContext(this,out, level);
                }

                void JXmlDocument::writeXml(JXmlWriteContext* context){
                    JWriter*  out = context->getWriter();

                    out->write(new JString("<?xml version=\"1.0\""));
                    out->write(new JString("?>"));
                    out->write(JSystem::lineSeparator());
                    out->write(JSystem::lineSeparator());

                    writeChildrenXml(context);
                }

                void JXmlDocument::writeChildrenXml(JXmlWriteContext* context){
                    jint length = getLength();
                    JWriter*  out = context->getWriter();

                    if (length == 0){
                        return;
                    }
                    for (jint i = 0; i < length; i++) {
                        (dynamic_cast<JNodeBase*>(item(i)))->writeXml(context);
                        out->write(JSystem::lineSeparator());
                    }
                }

                void JXmlDocument::checkChildType(jint type){
                    switch (type) {
                        case ELEMENT_NODE:
                        case PROCESSING_INSTRUCTION_NODE:
                        case COMMENT_NODE:
                        case DOCUMENT_TYPE_NODE:
                            return;
                        default:
                            throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                }

                void JXmlDocument::setSystemId(JString* uri){
                    systemId = uri;
                }

                JString* JXmlDocument::getSystemId(){
                    return systemId;
                }

                JNode* JXmlDocument::appendChild(JNode* n){
                    if ((dynamic_cast<JObject*>(n))->isInstanceOf(JElement::getClazz()) && getDocumentElement()!= null){
                        throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                    if ((dynamic_cast<JObject*>(n))->isInstanceOf(JDocumentType::getClazz()) && getDoctype()!= null){
                        throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                    return JParentNode::appendChild(n);
                }

                JNode* JXmlDocument::insertBefore(JNode* n, JNode* refNode){
                    if (!replaceRootElement && (dynamic_cast<JObject*>(n))->isInstanceOf(JElement::getClazz()) && getDocumentElement() != null){
                        throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                    if (!replaceRootElement && (dynamic_cast<JObject*>(n))->isInstanceOf(JDocumentType::getClazz()) && getDoctype() != null){
                        throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                    return JParentNode::insertBefore(n, refNode);
                }

                JNode* JXmlDocument::replaceChild(JNode* newChild, JNode* refChild){
                    if ((dynamic_cast<JObject*>(newChild))->isInstanceOf(JDocumentFragment::getClazz())) {
                        jint elemCount = 0;
                        jint docCount = 0;
                        replaceRootElement = false;
                        JParentNode* frag = dynamic_cast<JParentNode*>(newChild);
                        JNode* temp=null;
                        jint i = 0;
                        while ((temp = frag->item(i)) != null) {
                            if ((dynamic_cast<JObject*>(temp))->isInstanceOf(JElement::getClazz())){ 
                                elemCount++;

                            }else if ((dynamic_cast<JObject*>(temp))->isInstanceOf(JDocumentType::getClazz())){
                                docCount++;
                            }
                            i++;
                        }
                        if (elemCount > 1 || docCount > 1){
                            throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                        
                        }else{ 
                            replaceRootElement = true;
                        }
                    }
                    return JParentNode::replaceChild(newChild, refChild);
                }

                jshort JXmlDocument::getNodeType(){
                    return DOCUMENT_NODE;
                }

                JDocumentType* JXmlDocument::getDoctype(){
                    for (jint i = 0; true; i++) {
                        JNode* n = item(i);
                        if (n == null){
                            return null;
                        }
                        if ((dynamic_cast<JObject*>(n))->isInstanceOf(JDocumentType::getClazz())){
                            return dynamic_cast<JDocumentType*>(n);
                        }
                    }
                }

                JDocumentType* JXmlDocument::setDoctype(JString* dtdPublicId,JString*  dtdSystemId,JString*  internalSubset){
                    JDoctype* retval = dynamic_cast<JDoctype*>(getDoctype());

                    if (retval != null){
                        retval->setPrintInfo (dtdPublicId, dtdSystemId,internalSubset);

                    }else {
                        retval = new JDoctype(dtdPublicId, dtdSystemId,internalSubset);
                        retval->setOwnerDocument (this);
                        insertBefore(retval, getFirstChild());
                    }
                    return retval;
                }

                JElement* JXmlDocument::getDocumentElement(){
                    for (jint i = 0; true; i++) {
                        JNode* n = item(i);
                        if (n == null){
                            return null;
                        }
                        if ((dynamic_cast<JObject*>(n))->isInstanceOf(JElement::getClazz())) {
                            return dynamic_cast<JElement*>(n);
                        }
                    }
                }

                void JXmlDocument::setElementFactory(JElementFactory* factory){
                    this->factory = factory;
                }

                JElementFactory* JXmlDocument::getElementFactory(){
                    return factory;
                }

                JElement* JXmlDocument::createElement(JString* tagName){
                    return createElementEx(tagName);
                }

                JElement* JXmlDocument::createElementNS(JString* namespaceURI, JString* qualifiedName){
                    JElementNode2::checkArguments(namespaceURI, qualifiedName);
                    JElementNode2* retval = new JElementNode2(namespaceURI, qualifiedName);
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JElementEx* JXmlDocument::createElementEx(JString* tagName){
                    JElementNode* retval=null;
    
                    if (!JXmlNames::isName(tagName)) {
                        throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                    }

                    if (factory != null) {
                        retval = dynamic_cast<JElementNode*>(factory->createElementEx(tagName));
                        retval->setTag(tagName);
                    } else {
                        retval = new JElementNode(tagName);
                    }
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JElementEx* JXmlDocument::createElementEx(JString* uri, JString* tagName){
                    JElementNode* retval=null;
    
                    if (!JXmlNames::isName(tagName)) {
                        throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                    }

                    if (factory != null) {
                        retval = dynamic_cast<JElementNode*>(factory->createElementEx(uri, tagName));
                        retval->setTag(tagName);
                    } else {
                        retval = new JElementNode(tagName);
                    }
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JText* JXmlDocument::createTextNode(JString* text){
                    JTextNode* retval= new JTextNode();
                    retval->setOwnerDocument(this);
                    if (text != null){
                        retval->setText(text->toCharArray());
                    }
                    return retval;
                }

                JCDATASection* JXmlDocument::createCDATASection(JString* text){
                    JCDataNode* retval = new JCDataNode();
                    if (text != null){
                        retval->setText(text->toCharArray());
                    }
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JTextNode* JXmlDocument::newText (JPrimitiveCharArray* buf, jint offset, jint len){
                    JTextNode* retval = dynamic_cast<JTextNode*>(createTextNode(null));
                    JPrimitiveCharArray* data= new JPrimitiveCharArray(len);
                    JSystem::arraycopy(buf, offset, data, 0, len);
                    retval->setText(data);
                    return retval;
                }

                JProcessingInstruction* JXmlDocument::createProcessingInstruction(JString* target, JString* instructions){
                    if (!JXmlNames::isName(target)){
                        throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                    }

                    JPINode*  retval = new JPINode(target, instructions);
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JAttr* JXmlDocument::createAttribute(JString* name){
                    if (!JXmlNames::isName(name)) {
                        throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                    }
                    JAttributeNode1* retval = new JAttributeNode1(name, new JString(""), true, null);
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JAttr* JXmlDocument::createAttributeNS(JString* namespaceURI, JString* qualifiedName){
                    JAttributeNode::checkArguments(namespaceURI,qualifiedName);
                    JAttributeNode* retval = new JAttributeNode(namespaceURI, qualifiedName, new JString(""), true, null);
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JComment* JXmlDocument::createComment(JString* data){
                    JCommentNode* retval = new JCommentNode(data);
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JDocument* JXmlDocument::getOwnerDoc(){
                    return null;
                }

                JDOMImplementation* JXmlDocument::getImplementation(){
                    return JDOMImplementationImpl::getDOMImplementation();
                }

                JDocumentFragment* JXmlDocument::createDocumentFragment(){
                    JDocFragNode* retval = new JDocFragNode();
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JEntityReference* JXmlDocument::createEntityReference(JString* name){
                    if (!JXmlNames::isName(name)){
                        throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                    }

                    JEntityRefNode* retval = new JEntityRefNode(name);
                    retval->setOwnerDocument(this);
                    return retval;
                }

                JString* JXmlDocument::getNodeName(){
                    return new JString("#document");
                }

                JNode* JXmlDocument::cloneNode(jbool deep){
                    JXmlDocument* retval = new JXmlDocument();
                    retval->systemId = systemId;
                    if (deep) {
                        JNode* node=null;
                        for (jint i = 0; (node = item(i)) != null; i++) {
                            if (dynamic_cast<JObject*>(node)->isInstanceOf(JDocumentType::getClazz())) {
                                continue;
                            }
                            node = node->cloneNode(true);
                            retval->changeNodeOwner(node);
                            retval->appendChild(node);
                        }
                    }
                    return retval;
                }

                void JXmlDocument::changeNodeOwner(JNode* node){
                    JTreeWalker* walker=null;
                    JNodeBase* n=null;

                    if (node->getOwnerDocument () == this){
                        return;
                    }
                    if (!((dynamic_cast<JObject*>(node))->isInstanceOf(JNodeBase::getClazz()))){
                        throw new JDOMException(JDOMException::WRONG_DOCUMENT_ERR);
                    }

                    switch (node->getNodeType()){
                        case JNode::DOCUMENT_NODE:
                        case JNode::ENTITY_NODE:
                        case JNode::NOTATION_NODE:
                        case JNode::DOCUMENT_TYPE_NODE:
                            throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }

                    if ((dynamic_cast<JObject*>(node))->isInstanceOf(JAttributeNode::getClazz())) {
                        JAttributeNode* attr = dynamic_cast<JAttributeNode*>(node);
                        JElement* scope = attr->getOwnerElement();

                        if (scope != null && scope->getOwnerDocument () != this){
                            throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                        }
                    }

                    n = dynamic_cast<JNodeBase*>(node->getParentNode());
                    if (n != null){
                        n->removeChild(node);
                    }
                    
                    for (walker = new JTreeWalker (node), n =dynamic_cast<JNodeBase*>(walker->getCurrent()); n != null; n = dynamic_cast<JNodeBase*>(walker->getNext())) {
                        n->setOwnerDocument(this);
                        if ((dynamic_cast<JObject*>(n))->isInstanceOf(JElement::getClazz())) {
                            JNamedNodeMap* list = n->getAttributes();
                            jint length = list->getLength();
                            for (jint i = 0; i < length; i++){
                                changeNodeOwner(list->item(i));
                            }
                        }
                    }
                }

                JElement* JXmlDocument::getElementById(JString* elementId){
                    return getElementExById(elementId);
                }

                JElementEx* JXmlDocument::getElementExById(JString* id){
                    if (id == null){
                        throw new JIllegalArgumentException(new JString("null id"));
                    }

                    JTreeWalker* w = new JTreeWalker(this);
                    JElementEx* element=null;

                    while ((element = dynamic_cast<JElementEx*>(w->getNextElement(null))) != null){
                        JString* idAttr = element->getIdAttributeName();
                        JString* value=null;

                        if (idAttr == null){
                            continue;
                        }
                        value = element->getAttribute(idAttr);
                        if (value->equals(id)){
                            return element;
                        }
                    }
                    return null;
                }

                JNode* JXmlDocument::importNode(JNode* importedNode, jbool deep){
                    JNode* node = null;

                    switch (importedNode->getNodeType()){
                        case ATTRIBUTE_NODE:
                            node = importedNode->cloneNode(true);
                            break;

                        case DOCUMENT_FRAGMENT_NODE:
                            if (deep) {
                                node = importedNode->cloneNode(true);

                            } else {
                                node = new JDocFragNode();
                            }
                            break;

                        case DOCUMENT_NODE:
                        case DOCUMENT_TYPE_NODE:
                            throw new JDOMException(JDOMException::NOT_SUPPORTED_ERR);

                        case ELEMENT_NODE:
                            node = (dynamic_cast<JElementNode2*>(importedNode))->createCopyForImportNode(deep);
                            break;

                        case ENTITY_NODE:
                            node = importedNode->cloneNode(deep);
                            break;

                        case ENTITY_REFERENCE_NODE:
                            node = importedNode->cloneNode(false);
                            break;

                        case NOTATION_NODE:
                        case PROCESSING_INSTRUCTION_NODE:
                        case TEXT_NODE:
                        case CDATA_SECTION_NODE:
                        case COMMENT_NODE:
                        default:
                            node = importedNode->cloneNode(false);
                            break;
                    }

                    JTreeWalker* walker=null;
                    JNodeBase* n=null;
                    for (walker = new JTreeWalker (node), n = dynamic_cast<JNodeBase*>(walker->getCurrent()); n != null; n = dynamic_cast<JNodeBase*>(walker->getNext()) ) {
                        n->setOwnerDocument(this);

                        if (dynamic_cast<JObject*>(n)->isInstanceOf(JElement::getClazz())) {
                            JNamedNodeMap* list = n->getAttributes();
                            jint length = list->getLength();
                            for (jint i = 0; i < length; i++){
                                changeNodeOwner(list->item(i));
                            }
                        }
                    }
                    return node;
                }

                JString* JXmlDocument::getInputEncoding(){
                    throw new JException(new JString("TODO not implemented"));
                }

                JString* JXmlDocument::getXmlEncoding(){
                    throw new JException(new JString("TODO not implemented"));
                }

                jbool JXmlDocument::getXmlStandalone(){
                    throw new JException(new JString("TODO not implemented"));
                }

                void JXmlDocument::setXmlStandalone(jbool xmlStandalone){
                    throw new JException(new JString("TODO not implemented"));
                }

                JString* JXmlDocument::getXmlVersion(){
                    throw new JException(new JString("TODO not implemented"));
                }

                void JXmlDocument::setXmlVersion(JString* xmlVersion){
                    throw new JException(new JString("TODO not implemented"));
                }

                jbool JXmlDocument::getStrictErrorChecking(){
                    throw new JException(new JString("TODO not implemented"));
                }

                void JXmlDocument::setStrictErrorChecking(jbool strictErrorChecking){
                    throw new JException(new JString("TODO not implemented"));
                }

                JString* JXmlDocument::getDocumentURI(){
                    throw new JException(new JString("TODO not implemented"));
                }

                void JXmlDocument::setDocumentURI(JString* documentURI){
                    throw new JException(new JString("TODO not implemented"));
                }

                JNodeList* JXmlDocument::getElementsByTagName(JString* tagname){
                    throw new JException(new JString("TODO not implemented"));
                }

                JNodeList* JXmlDocument::getElementsByTagNameNS(JString* namespaceURI,JString* localName){
                    throw new JException(new JString("TODO not implemented"));
                }

                JNode* JXmlDocument::adoptNode(JNode* source){
                    throw new JException(new JString("TODO not implemented"));
                }

                JDOMConfiguration* JXmlDocument::getDomConfig(){
                    throw new JException(new JString("TODO not implemented"));
                }

                void JXmlDocument::normalizeDocument(){
                    throw new JException(new JString("TODO not implemented"));
                }

                JNode* JXmlDocument::renameNode(JNode* n,JString* namespaceURI,JString* qualifiedName){
                    throw new JException(new JString("TODO not implemented"));
                }

                JXmlDocument::~JXmlDocument(){
                }
            }
        }
    }
}
