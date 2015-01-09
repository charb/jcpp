#ifndef ORG_XML_SAX_EXT_DECL_HANDLER_H
#define ORG_XML_SAX_EXT_DECL_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JAttributes.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

            	// @Class(canonicalName="org.xml.sax.ext.DeclHandler", simpleName="DeclHandler");
                class JCPP_EXPORT JDeclHandler : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void elementDecl(JString* name, JString* model)=0;

                    virtual void attributeDecl(JString* eName,JString* aName,JString* type,JString* mode,JString* value)=0;

                    virtual void internalEntityDecl(JString* name, JString* value)=0;

                    virtual void externalEntityDecl(JString* name, JString* publicId,JString* systemId)=0;

                    virtual ~JDeclHandler();
                };
            }
        }
    }
}

#endif
