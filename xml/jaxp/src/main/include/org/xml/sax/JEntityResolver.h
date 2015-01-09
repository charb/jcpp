#ifndef ORG_XML_SAX_ENTITY_RESOLVER_H
#define ORG_XML_SAX_ENTITY_RESOLVER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JInputSource.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.EntityResolver", simpleName="EntityResolver");
            class JCPP_EXPORT JEntityResolver : public JInterface{
            public:
                static JClass* getClazz();

                virtual JInputSource* resolveEntity(JString* publicId,JString* systemId)=0;

                virtual ~JEntityResolver();
            };
        }
    }
}

#endif
