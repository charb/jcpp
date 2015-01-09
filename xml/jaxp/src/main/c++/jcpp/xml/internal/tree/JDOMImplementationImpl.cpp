#include "jcpp/xml/internal/tree/JDOMImplementationImpl.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/xml/internal/tree/JDoctype.h"
#include "jcpp/xml/internal/util/JXmlNames.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JDOMException.h"

using namespace org::w3c::dom;
using namespace jcpp::xml::internal::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JDOMImplementationImpl* JDOMImplementationImpl::singleton = new JDOMImplementationImpl();
                
                jbool JDOMImplementationImpl::hasFeature0(JString* feature, JString* version){
                    if ((new JString("XML"))->equalsIgnoreCase(feature) || (new JString("Core"))->equalsIgnoreCase(feature)) {
                        if (version == null || (new JString(""))->equals(version) || (new JString("2.0"))->equals(version) || (new JString("1.0"))->equals(version)) {
                            return true;
                        }
                    }
                    return false;
                }

                JDOMImplementationImpl::JDOMImplementationImpl():JObject(getClazz()){
                }
                
                JDOMImplementation* JDOMImplementationImpl::getDOMImplementation(){
                    return singleton;
                }

                jbool JDOMImplementationImpl::hasFeature(JString* feature, JString* version){
                    return hasFeature0(feature,version);
                }

                JObject* JDOMImplementationImpl::getFeature(JString* feature,JString* version){
                    throw new JDOMException(JDOMException::INVALID_ACCESS_ERR);
                }

                JDocumentType* JDOMImplementationImpl::createDocumentType(JString* qualifiedName,JString* publicId,JString* systemId){
                    if (!JXmlNames::isName(qualifiedName)) {
                        throw new JDOMException(JDOMException::INVALID_CHARACTER_ERR);
                    }
                    if (!JXmlNames::isQualifiedName(qualifiedName)) {
                        throw new JDOMException(JDOMException::NAMESPACE_ERR);
                    }

                    return new JDoctype(qualifiedName, publicId, systemId,null);
                }

                JDocument* JDOMImplementationImpl::createDocument(JString* namespaceURI, JString* qualifiedName,JDocumentType* doctype){
                    JDocument* doc = new JXmlDocument();
                    if (doctype != null) {
                        doc->appendChild(doctype);
                    }
                    JElement* docElement = doc->createElementNS(namespaceURI, qualifiedName);
                    doc->appendChild(docElement);
                    return doc;
                }

                JDOMImplementationImpl::~JDOMImplementationImpl(){
                }
            }
        }
    }
}
