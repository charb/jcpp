#ifndef ORG_XML_SAX_HELPERS_XML_READER_FACTORY_H
#define ORG_XML_SAX_HELPERS_XML_READER_FACTORY_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JXMLReader.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

            	// @Class(canonicalName="org.xml.sax.helpers.XMLReaderFactory", simpleName="XMLReaderFactory");
                class JCPP_EXPORT JXMLReaderFactory : public JObject{
                public:
                    static JClass* getClazz();

                    static JXMLReader* createXMLReader();

                    static JXMLReader* createXMLReader(JString* className);

                    virtual ~JXMLReaderFactory();
                };
            }
        }
    }
}

#endif
