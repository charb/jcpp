#include "jcpp/xml/internal/tree/JXmlDocumentBuilderNS.h"
#include "jcpp/xml/internal/tree/JAttributeSet.h"
#include "jcpp/xml/internal/tree/JElementNode2.h"
#include "jcpp/xml/internal/parser/JAttributesEx.h"
#include "org/xml/sax/JSAXParseException.h"

using namespace jcpp::xml::internal::parser;
using namespace org::xml::sax;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JXmlDocumentBuilderNS::JXmlDocumentBuilderNS():JXmlDocumentBuilder(getClazz()){
                }

                void JXmlDocumentBuilderNS::startElement(JString* namespaceURI, JString* localName,JString* qName, JAttributes* attributes){
                    JAttributeSet* attSet = null;
                    jint length = attributes->getLength();
                    if (length != 0) {
                        attSet = JAttributeSet::createAttributeSet2(attributes);
                    }

                    if ((new JString(""))->equals(namespaceURI)) {
                        namespaceURI = null;
                    }
                    JElementNode2* e = dynamic_cast<JElementNode2*>(document->createElementNS(namespaceURI, qName));

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

                void JXmlDocumentBuilderNS::processingInstruction(JString* name, JString* instruction){
                    if (name->indexOf(':') != -1) {
                        throw new JSAXParseException();
                    }
                    JXmlDocumentBuilder::processingInstruction(name, instruction);
                }

                void JXmlDocumentBuilderNS::internalEntityDecl(JString* name, JString* value){
                    if (name->indexOf(':') != -1) {
                        throw new JSAXParseException();
                    }
                    JXmlDocumentBuilder::internalEntityDecl(name, value);
                }

                void JXmlDocumentBuilderNS::externalEntityDecl(JString* name, JString* publicId,JString* systemId){
                    if (name->indexOf(':') != -1) {
                        throw new JSAXParseException();
                    }
                    JXmlDocumentBuilder::externalEntityDecl(name, publicId, systemId);
                }

                void JXmlDocumentBuilderNS::notationDecl(JString* n, JString* p, JString* s){
                    if (n->indexOf(':')!= -1) {
                        throw new JSAXParseException();
                    }
                    JXmlDocumentBuilder::notationDecl(n, p, s);
                }

                void JXmlDocumentBuilderNS::unparsedEntityDecl(JString* name, JString* publicId, JString* systemId, JString* notation){
                    if (name->indexOf(':')!= -1) {
                        throw new JSAXParseException();
                    }
                    JXmlDocumentBuilder::unparsedEntityDecl(name, publicId, systemId, notation);
                }

                JXmlDocumentBuilderNS::~JXmlDocumentBuilderNS(){
                }
            }
        }
    }
}
