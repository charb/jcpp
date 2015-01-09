#ifndef ORG_XML_SAX_ERROR_HANDLER_H
#define ORG_XML_SAX_ERROR_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JSAXParseException.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.ErrorHandler", simpleName="ErrorHandler");
            class JCPP_EXPORT JErrorHandler : public JInterface{
            public:
                static JClass* getClazz();

                virtual void warning(JSAXParseException* exception)=0;

                virtual void error(JSAXParseException* exception)=0;

                virtual void fatalError(JSAXParseException* exception)=0;

                virtual ~JErrorHandler();
            };
        }
    }
}

#endif
