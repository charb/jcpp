#ifndef ORG_XML_SAX_XML_FILTER_H
#define ORG_XML_SAX_XML_FILTER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JXMLReader.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.XMLFilter", simpleName="XMLFilter");
            class JCPP_EXPORT JXMLFilter : public JXMLReader{
            public:
                static JClass* getClazz();

                virtual void setParent(JXMLReader* parent)=0;

                virtual JXMLReader* getParent()=0;

                virtual ~JXMLFilter();
            };
        }
    }
}

#endif
