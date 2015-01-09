#include "jcpp/xml/internal/tree/JXmlDocumentBuilder.h"
#include "jcpp/xml/internal/tree/JAttributeSet.h"
#include "jcpp/xml/internal/tree/JElementNode.h"
#include "jcpp/xml/internal/tree/JPINode.h"
#include "jcpp/xml/internal/parser/JAttributesEx.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/io/JOutputStreamWriter.h"
#include "jcpp/lang/JException.h"
#include "org/xml/sax/helpers/JXMLReaderFactory.h"
#include "org/xml/sax/JXMLReader.h"
#include "org/w3c/dom/JDOMException.h"
#include "org/w3c/dom/JDOMImplementation.h"

using namespace jcpp::io;
using namespace org::xml::sax;
using namespace org::xml::sax::helpers;
using namespace jcpp::xml::internal::parser;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JXmlDocumentBuilder::JXmlDocumentBuilder(JClass* _class):JObject(_class){
                    document=null;
                    locator=null;
                    factory=null;
                    attrTmp=new JVector();
                    elementStack=null;
                    topOfStack=0;
                    inDTD=false;
                    inCDataSection=false;
                    doctype=null;
                    disableNamespaces=true;    
                    ignoreWhitespace=false;
                    expandEntityRefs=true;
                    ignoreComments=false;
                    putCDATAIntoText=false;
                }

                JXmlDocumentBuilder::JXmlDocumentBuilder():JObject(getClazz()){
                    document=null;
                    locator=null;
                    factory=null;
                    attrTmp=new JVector();
                    elementStack=null;
                    topOfStack=0;
                    inDTD=false;
                    inCDataSection=false;
                    doctype=null;
                    disableNamespaces=true;    
                    ignoreWhitespace=false;
                    expandEntityRefs=true;
                    ignoreComments=false;
                    putCDATAIntoText=false;
                }

                jbool JXmlDocumentBuilder::isIgnoringLexicalInfo(){
                    return ignoreWhitespace && expandEntityRefs && ignoreComments && putCDATAIntoText;
                }

                void JXmlDocumentBuilder::setIgnoringLexicalInfo(jbool value){
                    ignoreWhitespace = value;
                    expandEntityRefs = value;
                    ignoreComments = value;
                    putCDATAIntoText = value;
                }

                void JXmlDocumentBuilder::setIgnoreWhitespace(jbool value){
                    ignoreWhitespace = value;
                }

                void JXmlDocumentBuilder::setExpandEntityReferences(jbool value){
                    expandEntityRefs = value;
                }

                void JXmlDocumentBuilder::setIgnoreComments(jbool value){
                    ignoreComments = value;
                }

                void JXmlDocumentBuilder::setPutCDATAIntoText(jbool value){
                    putCDATAIntoText = value;
                }

                jbool JXmlDocumentBuilder::getDisableNamespaces(){
                    return disableNamespaces;
                }

                void JXmlDocumentBuilder::setDisableNamespaces(jbool value){
                    disableNamespaces = value;
                }

                JXmlDocument* JXmlDocumentBuilder::getDocument(){
                    return document;
                }

                void JXmlDocumentBuilder::setDocumentLocator(JLocator* locator){
                    this->locator = locator;
                }

                JXmlDocument* JXmlDocumentBuilder::createDocument(){
                    JXmlDocument* retval = new JXmlDocument();
                    if (factory != null) {
                        retval->setElementFactory(factory);
                    }
                    return retval;
                }

                void JXmlDocumentBuilder::setElementFactory(JElementFactory* factory){
                    this->factory = factory;
                }

                JElementFactory* JXmlDocumentBuilder::getElementFactory(){
                    return factory;
                }

                void JXmlDocumentBuilder::startDocument(){
                    document = createDocument();
                    if (locator != null){
                        document->setSystemId(locator->getSystemId());
                    }
                    elementStack = new JPrimitiveObjectArray(JParentNode::getClazz(),200);
                    topOfStack = 0;
                    elementStack->set(topOfStack, document);
                    inDTD = false;
                }

                void JXmlDocumentBuilder::endDocument(){
                    if (topOfStack != 0){
                        throw new JIllegalStateException();
                    }
                    document->trimToSize();
                }

                void JXmlDocumentBuilder::startPrefixMapping(JString* prefix, JString* uri){
                }

                void JXmlDocumentBuilder::endPrefixMapping(JString* prefix){
                }

                void JXmlDocumentBuilder::startElement(JString* namespaceURI, JString* localName,JString* qName, JAttributes* attributes){
                    JAttributeSet* attSet = null;
                    jint length = attributes->getLength();
                    if (length != 0) {
                        attSet = JAttributeSet::createAttributeSet1(attributes);
                    }

                    JElementNode* e = dynamic_cast<JElementNode*>(document->createElementEx(qName));
                    if (dynamic_cast<JObject*>(attributes)->isInstanceOf(JAttributesEx::getClazz())) {
                        e->setIdAttributeName((dynamic_cast<JAttributesEx*>(attributes))->getIdAttributeName());
                    }
                    if (length != 0) {
                        e->setAttributes(attSet);
                    }

                    JParentNode* p=dynamic_cast<JParentNode*>(elementStack->get(topOfStack++));
                    p->appendChild(e);
                    elementStack->set(topOfStack, e);           
                }

                void JXmlDocumentBuilder::endElement(JString* namespaceURI, JString* localName,JString* qName){
                    JParentNode* e = dynamic_cast<JParentNode*>(elementStack->get(topOfStack));
                    elementStack->set(topOfStack--, null);
                    e->reduceWaste();
                }

                void JXmlDocumentBuilder::characters(JPrimitiveCharArray* buf, jint offset, jint len){
                    JParentNode*  top = dynamic_cast<JParentNode*>(elementStack->get(topOfStack));

                    if (inCDataSection) {
                        JString* temp = new JString (buf, offset, len);
                        JCDATASection* section =dynamic_cast<JCDATASection*>(top->getLastChild());
                        section->appendData(temp);
                        return;
                    }

                    JNodeBase* lastChild = dynamic_cast<JNodeBase*>(top->getLastChild());
                    if (lastChild != null && dynamic_cast<JObject*>(lastChild)->getClass() == JTextNode::getClazz()) {
                        JString* tmp  = new JString (buf, offset, len);
                        (dynamic_cast<JTextNode*>(lastChild))->appendData(tmp);
                    } else {
                        JTextNode* text = document->newText(buf, offset, len);
                        top->appendChild(text);
                    }
                }

                void JXmlDocumentBuilder::ignorableWhitespace(JPrimitiveCharArray* buf , jint offset, jint len){
                    if (ignoreWhitespace){
                        return;
                    }

                    characters(buf, offset, len);
                }

                void JXmlDocumentBuilder::processingInstruction(JString* name, JString* instruction){
                    if (inDTD){
                        return;
                    }
                    JParentNode*  top = dynamic_cast<JParentNode*>(elementStack->get(topOfStack));
                    JPINode* pi=dynamic_cast<JPINode*>(document->createProcessingInstruction(name,instruction));
                    top->appendChild(pi);
                }

                void JXmlDocumentBuilder::skippedEntity(JString* name){
                }

                void JXmlDocumentBuilder::startDTD(JString* name, JString* publicId, JString* systemId){
                    JDOMImplementation* impl = document->getImplementation();
                    doctype = dynamic_cast<JDoctype*>(impl->createDocumentType(name, publicId, systemId));
                    doctype->setOwnerDocument(document);
                    inDTD = true;
                }

                void JXmlDocumentBuilder::endDTD(){
                    document->appendChild(doctype);
                    inDTD = false;
                }

                void JXmlDocumentBuilder::startEntity(JString* name){
                    if (expandEntityRefs || inDTD) {
                        return;
                    }

                    JEntityReference* e = document->createEntityReference(name);
                    JParentNode* p=dynamic_cast<JParentNode*>(elementStack->get(topOfStack++));
                    p->appendChild(e);
                    elementStack->set(topOfStack, dynamic_cast<JObject*>(e));
                }

                void JXmlDocumentBuilder::endEntity(JString* name){
                    if (inDTD) {
                        return;
                    }

                    JParentNode* entity = dynamic_cast<JParentNode*>(elementStack->get(topOfStack));

                    if (!(entity->isInstanceOf(JEntityReference::getClazz()))){
                        return;
                    }

                    entity->setReadonly(true);
                    elementStack->set(topOfStack--, null);
                    if (!name->equals(entity->getNodeName())) {
                        throw new JSAXParseException(new JString("ending another entity name"));
                    }
                }

                void JXmlDocumentBuilder::startCDATA(){
                    if (putCDATAIntoText) {
                        return;
                    }

                    JCDATASection* text = document->createCDATASection(new JString(""));
                    JParentNode* top = dynamic_cast<JParentNode*>(elementStack->get(topOfStack));
                    
                    inCDataSection = true;
                    top->appendChild(text);
                }

                void JXmlDocumentBuilder::endCDATA(){
                    inCDataSection = false;
                }

                void JXmlDocumentBuilder::comment(JPrimitiveCharArray* ch, jint start, jint length){
                    if (ignoreComments || inDTD) {
                        return;
                    }

                    JString* text = new JString(ch, start, length);
                    JComment* comment = document->createComment(text);
                    JParentNode* top = dynamic_cast<JParentNode*>(elementStack->get(topOfStack));    
                    top->appendChild(comment);
                }

                void JXmlDocumentBuilder::elementDecl(JString* name, JString* model){
                }

                void JXmlDocumentBuilder::attributeDecl(JString* eName, JString* aName, JString* type,JString* valueDefault, JString* value){
                }

                void JXmlDocumentBuilder::internalEntityDecl(JString* name, JString* value){
                    if (!name->startsWith(new JString("%"))) {
                        doctype->addEntityNode(name, value);
                    }
                }

                void JXmlDocumentBuilder::externalEntityDecl(JString* name, JString* publicId,JString* systemId){
                    if (!name->startsWith(new JString("%"))) {
                        doctype->addEntityNode(name, publicId, systemId, null);
                    }
                }

                void JXmlDocumentBuilder::notationDecl(JString* n, JString* p, JString* s){
                    doctype->addNotation(n, p, s);
                }

                void JXmlDocumentBuilder::unparsedEntityDecl(JString* name, JString* publicId, JString* systemId, JString* notation){
                    doctype->addEntityNode(name, publicId, systemId, notation);
                }

                JXmlDocumentBuilder::~JXmlDocumentBuilder(){
                }
            }
        }
    }
}
