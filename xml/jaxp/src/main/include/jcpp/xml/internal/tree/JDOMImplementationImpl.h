#ifndef JCPP_XML_INTERNAL_TREE_DOM_IMPLEMENTATION_IMPL_H
#define JCPP_XML_INTERNAL_TREE_DOM_IMPLEMENTATION_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JElementEx.h"
#include "org/w3c/dom/JDOMImplementation.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{            

            	// @Class(canonicalName="javax.xml.internal.tree.DOMImplementationImpl", simpleName="DOMImplementationImpl");
            	class JCPP_EXPORT JDOMImplementationImpl : public JObject, public JDOMImplementation{
                protected:
                    static JDOMImplementationImpl* singleton;
                    static jbool hasFeature0(JString* feature, JString* version);
                    friend class JNodeBase;

                public:
                    JDOMImplementationImpl();
                    
                    static JClass* getClazz();

                    static JDOMImplementation* getDOMImplementation();

                    virtual jbool hasFeature(JString* feature, JString* version);

                    virtual JObject* getFeature(JString* feature,JString* version);

                    virtual JDocumentType* createDocumentType(JString* qualifiedName,JString* publicId,JString* systemId);

                    virtual JDocument* createDocument(JString* namespaceURI, JString* qualifiedName,JDocumentType* doctype);

                    virtual ~JDOMImplementationImpl();
                };
            }
        }
    }
}

#endif
