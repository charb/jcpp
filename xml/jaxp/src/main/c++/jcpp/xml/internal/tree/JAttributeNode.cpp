#include "jcpp/xml/internal/tree/JAttributeNode.h"
#include "jcpp/xml/internal/tree/JTextNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/xml/internal/util/JXmlNames.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"
#include "jcpp/lang/JException.h"

using namespace jcpp::xml::internal::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JAttributeNode::JAttributeNode(JClass* _class,JString* namespaceURI, JString* qName,JString* value, jbool specified, JString* defaultValue):JNamespacedNode(_class,namespaceURI,qName){
                    this->value=value;
                    this->specified=specified;
                    this->defaultValue=defaultValue;
                }

                JAttributeNode::JAttributeNode(JString* namespaceURI, JString* qName,JString* value, jbool specified, JString* defaultValue):JNamespacedNode(getClazz(),namespaceURI,qName){
                    this->value=value;
                    this->specified=specified;
                    this->defaultValue=defaultValue;
                }

                JAttributeNode* JAttributeNode::makeClone(){
                    JAttributeNode* retval = new JAttributeNode(namespaceURI, qName, value,specified, defaultValue);
                    retval->ownerDocument = ownerDocument;
                    return retval;
                }

                void JAttributeNode::checkArguments(JString* namespaceURI, JString* qualifiedName){
                    if (qualifiedName == null) {
                        throw new JDOMException(JDOMException::NAMESPACE_ERR);
                    }

                    jint first = qualifiedName->indexOf(':');

                    if (first <= 0) {
                        if (!JXmlNames::isUnqualifiedName(qualifiedName)) {
                            throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                        }
                        if ((new JString("xmlns"))->equals(qualifiedName) && !JXmlNames::SPEC_XMLNS_URI->equals(namespaceURI)) {
                            throw new JDOMException(JDOMException::NAMESPACE_ERR);
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

                    if (namespaceURI == null || ((new JString("xml"))->equals(prefix) && !JXmlNames::SPEC_XML_URI->equals(namespaceURI))) {
                        throw new JDOMException(JDOMException::NAMESPACE_ERR);
                    }
                }

                JString* JAttributeNode::getDefaultValue(){
                    return defaultValue;
                }

                JElement* JAttributeNode::getOwnerElement(){
                    return ownerElement;
                }

                void JAttributeNode::setOwnerElement(JElement* element){
                    if (element != null && ownerElement != null) {
                        throw new JIllegalStateException();
                    }
                    ownerElement = element;
                }

                jshort JAttributeNode::getNodeType(){
                    return ATTRIBUTE_NODE;
                }

                JString* JAttributeNode::getName(){
                    return qName;
                }

                JString* JAttributeNode::getValue(){
                    return value;
                }

                void JAttributeNode::setValue(JString* value){
                    setNodeValue (value);
                }

                JString* JAttributeNode::getNodeValue(){
                    return value;
                }

                jbool JAttributeNode::getSpecified(){
                    return specified;
                }

                void JAttributeNode::setNodeValue(JString* value){
                    if (isReadonly ()){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    this->value = value;
                    specified = true;
                }

                void JAttributeNode::setSpecified(jbool specified){
                    this->specified = specified;
                }

                JNode* JAttributeNode::getParentNode(){
                    return null;
                }

                JNode* JAttributeNode::getNextSibling(){
                    return null;
                }

                JNode* JAttributeNode::getPreviousSibling(){
                    return null;
                }

                void JAttributeNode::writeXml(JXmlWriteContext* context){
                    JWriter*  out = context->getWriter();
                    out->write(qName);
                    out->write(new JString("=\""));
                    writeChildrenXml(context);
                    out->write('"');
                }

                void JAttributeNode::writeChildrenXml(JXmlWriteContext* context){
                    JWriter* out = context->getWriter();
                    for (jint i = 0; i < value->length(); i++) {
                        jint c = value->charAt(i);
                        switch (c) {
                            case '<':  
                                out->write(new JString("&lt;")); 
                                continue;
                            
                            case '>':  
                                out->write(new JString("&gt;")); 
                                continue;
                            
                            case '&':  
                                out->write(new JString("&amp;")); 
                                continue;
                          
                            case '\'': 
                                out->write(new JString("&apos;")); 
                                continue;
                          
                            case '"':  
                                out->write(new JString("&quot;")); 
                                continue;
                          
                            default:   
                                out->write(c); 
                                continue;
                        }
                    }
                }

                JNode* JAttributeNode::cloneNode(jbool deep){
                    JAttributeNode* attr = cloneAttributeNode(deep);
                    attr->specified = true;
                    return attr;
                }

                JAttributeNode* JAttributeNode::cloneAttributeNode(jbool deep){
                    JAttributeNode* attr = makeClone();
                    if (deep) {
                        JNode* node=null;
                        for (jint i = 0; (node = item(i)) != null; i++) {
                            node = node->cloneNode(true);
                            attr->appendChild(node);
                        }
                    }
                    return attr;
                }

                void JAttributeNode::checkChildType(jint type){
                    switch(type) {
                        case TEXT_NODE:
                        case ENTITY_REFERENCE_NODE:
                            return;
                        default:
                            throw new JDOMException(JDOMException::HIERARCHY_REQUEST_ERR);
                    }
                }

                JTypeInfo* JAttributeNode::getSchemaTypeInfo(){
                    throw new JException(new JString("TODO not implemented"));
                }

                jbool JAttributeNode::isId(){
                    throw new JException(new JString("TODO not implemented"));
                }

                JAttributeNode::~JAttributeNode(){
                }
            }
        }
    }
}
