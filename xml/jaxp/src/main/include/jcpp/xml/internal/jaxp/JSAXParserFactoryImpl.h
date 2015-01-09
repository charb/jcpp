#ifndef JCPP_XML_INTERNAL_JAXP_SAX_PARSER_FACTORY_IMPL_H
#define JCPP_XML_INTERNAL_JAXP_SAX_PARSER_FACTORY_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/parsers/JSAXParser.h"
#include "jcpp/xml/parsers/JSAXParserFactory.h"
#include "jcpp/xml/internal/jaxp/JSAXParserImpl.h"

using namespace jcpp::xml::parsers;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace jaxp{

            	// @Class(canonicalName="javax.xml.internal.jaxp.SAXParserFactoryImpl", simpleName="SAXParserFactoryImpl");
                class JCPP_EXPORT JSAXParserFactoryImpl : public JSAXParserFactory{
                protected:
                    JHashtable* features;

                public:
                    JSAXParserFactoryImpl();

                    static JClass* getClazz();

                    virtual JSAXParser* newSAXParser();

                    virtual JSAXParserImpl* newSAXParserImpl();

                    virtual void setFeature(JString* name,jbool value);

                    virtual jbool getFeature(JString* name);

                    virtual ~JSAXParserFactoryImpl();
                };
            }
        }
    }
}

#endif
