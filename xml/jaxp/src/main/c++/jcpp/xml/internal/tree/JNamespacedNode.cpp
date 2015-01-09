#include "jcpp/xml/internal/tree/JNamespacedNode.h"
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

                JNamespacedNode::JNamespacedNode(JClass* _class,JString* namespaceURI,JString* qName):JParentNode(_class){
                    this->qName=qName;
                    this->namespaceURI=namespaceURI;
                }

                JString* JNamespacedNode::getNamespaceURI(){
                    return namespaceURI;
                }

                JString* JNamespacedNode::getPrefix(){
                    return JXmlNames::getPrefix(qName);
                }

                void JNamespacedNode::setPrefix(JString* prefix){
                    if (readonly) {
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    jint index = qName->indexOf(':');
                    if (prefix == null) {
                        if (index >= 0) {
                            qName = qName->substring(index + 1);
                        }
                        return;
                    }

                    if (!JXmlNames::isUnqualifiedName(prefix)) {
                        throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                    }

                    if (namespaceURI == null || (new JString("xml"))->equals(prefix) && !JXmlNames::SPEC_XML_URI->equals(namespaceURI)) {
                        throw new JDOMException(JDOMException::NAMESPACE_ERR);
                    }

                    if (getNodeType() == ATTRIBUTE_NODE) {
                        if ((new JString("xmlns"))->equals(prefix) && !JXmlNames::SPEC_XMLNS_URI->equals(namespaceURI) || (new JString("xmlns"))->equals(qName)) {
                            throw new JDOMException(JDOMException::NAMESPACE_ERR);
                        }
                    }

                    JStringBuffer* tmp = new JStringBuffer(prefix);
                    tmp->append(':');
                    if (index < 0 ) {
                        tmp->append(qName);
                    
                    } else {
                        tmp->append(qName->substring(index + 1));
                    }
                    qName = tmp->toString();
                }

                JString* JNamespacedNode::getLocalName(){
                    return JXmlNames::getLocalPart(qName);
                }

                JString* JNamespacedNode::getNodeName(){
                    return qName;
                }

                JNamespacedNode::~JNamespacedNode(){
                }
            }
        }
    }
}
