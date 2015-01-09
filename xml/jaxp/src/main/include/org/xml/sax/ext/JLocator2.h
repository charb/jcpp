#ifndef ORG_XML_SAX_EXT_LOCATOR2_H
#define ORG_XML_SAX_EXT_LOCATOR2_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JLocator.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

            	// @Class(canonicalName="org.xml.sax.ext.Locator2", simpleName="Locator2");
                class JCPP_EXPORT JLocator2 : public virtual JLocator{
                public:
                    static JClass* getClazz();

                    virtual JString* getXMLVersion()=0;
                    
                    virtual JString* getEncoding()=0;

                    virtual ~JLocator2();
                };
            }
        }
    }
}

#endif
