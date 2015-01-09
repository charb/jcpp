#ifndef JCPP_XML_INTERNAL_JAXP_DEFAULT_VALIDATION_ERROR_HANDLER_H
#define JCPP_XML_INTERNAL_JAXP_DEFAULT_VALIDATION_ERROR_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/helpers/JDefaultHandler.h"
#include "org/xml/sax/JSAXParseException.h"

using namespace org::xml::sax;
using namespace org::xml::sax::helpers;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace jaxp{

            	// @Class(canonicalName="javax.xml.internal.jaxp.DefaultValidationErrorHandler", simpleName="DefaultValidationErrorHandler");
                class JCPP_EXPORT JDefaultValidationErrorHandler : public JDefaultHandler{
                protected:
                    jint errorCount;

                public:
                    JDefaultValidationErrorHandler();

                    static JClass* getClazz();

                    virtual void error(JSAXParseException* e);

                    virtual ~JDefaultValidationErrorHandler();
                };
            }
        }
    }
}

#endif
