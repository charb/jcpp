#ifndef JCPP_XML_PARSERS_PARSER_CONFIGURATION_EXCEPTION_H
#define JCPP_XML_PARSERS_PARSER_CONFIGURATION_EXCEPTION_H

#include "jcpp/lang/JError.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace xml{
        namespace parsers{

        	// @Class(canonicalName="javax.xml.parsers.ParserConfigurationException", simpleName="ParserConfigurationException");
            class JCPP_EXPORT JParserConfigurationException : public JException{
            protected:
                JParserConfigurationException(jcpp::lang::JClass* _class);

            public:
                JParserConfigurationException(JString* message);

                static jcpp::lang::JClass* getClazz();

                virtual ~JParserConfigurationException();
            };
        }
    }
}
#endif
