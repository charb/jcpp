#ifndef ORG_XML_SAX_LOCATOR_H
#define ORG_XML_SAX_LOCATOR_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.Locator", simpleName="Locator");
            class JCPP_EXPORT JLocator : public JInterface{
            public:
                static JClass* getClazz();

                virtual JString* getPublicId()=0;

                virtual JString* getSystemId()=0;

                virtual jint getLineNumber()=0;

                virtual jint getColumnNumber()=0;

                virtual ~JLocator();
            };
        }
    }
}

#endif
