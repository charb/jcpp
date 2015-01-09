#ifndef ORG_XML_SAX_HELPERS_PARSER_FACTORY_H
#define ORG_XML_SAX_HELPERS_PARSER_FACTORY_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JParser.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

            	// @Class(canonicalName="org.xml.sax.helpers.ParserFactory", simpleName="ParserFactory");
                class JCPP_EXPORT JParserFactory : public JObject{
                public:
                    static JClass* getClazz();

                    static JParser* makeParser();

                    static JParser* makeParser(JString* className);

                    virtual ~JParserFactory();
                };
            }
        }
    }
}

#endif
