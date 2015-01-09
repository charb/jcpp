#ifndef ORG_XML_SAX_EXT_ENTITY_RESOLVER2_H
#define ORG_XML_SAX_EXT_ENTITY_RESOLVER2_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JInputSource.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

            	// @Class(canonicalName="org.xml.sax.ext.EntityResolver2", simpleName="EntityResolver2");
                class JCPP_EXPORT JEntityResolver2 : public JEntityResolver{
                public:
                    static JClass* getClazz();

                    virtual JInputSource* getExternalSubset(JString* name, JString* baseURI)=0;
                    
                    virtual JInputSource* resolveEntity(JString* name,JString* publicId,JString* baseURI,JString* systemId)=0;

                    virtual ~JEntityResolver2();
                };
            }
        }
    }
}

#endif
