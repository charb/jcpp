#ifndef JCPP_XML_PARSERS_FACTORY_CONFIGURATION_ERROR_H
#define JCPP_XML_PARSERS_FACTORY_CONFIGURATION_ERROR_H

#include "jcpp/lang/JError.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace xml{
        namespace parsers{

        	// @Class(canonicalName="javax.xml.parsers.FactoryConfigurationError", simpleName="FactoryConfigurationError");
            class JCPP_EXPORT JFactoryConfigurationError : public JError{
            protected:
                JException* exception;
                JFactoryConfigurationError(jcpp::lang::JClass* _class);
                friend class JFactoryConfigurationErrorClass;

            public:
                JFactoryConfigurationError(JString* message,JException* e);

                static jcpp::lang::JClass* getClazz();

                virtual JException* getException();

                virtual ~JFactoryConfigurationError();
            };
        }
    }
}
#endif
