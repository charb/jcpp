#include "jcpp/xml/internal/jaxp/JDefaultValidationErrorHandler.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace jaxp{

                JDefaultValidationErrorHandler::JDefaultValidationErrorHandler():JDefaultHandler(getClazz()){
                    errorCount=0;
                }

                void JDefaultValidationErrorHandler::error(JSAXParseException* e){
                    if (errorCount >= 10) {
                        return;

                    } else if (errorCount == 0) {
                        JSystem::err->println(new JString("Warning: validation was turned on but an org.xml.sax.ErrorHandler was not"));
                        JSystem::err->println(new JString("set, which is probably not what is desired.  Parser will use a default"));
                        JSystem::err->println(new JString("ErrorHandler to print the first 10 errors.  Please call"));
                        JSystem::err->println(new JString("the 'setErrorHandler' method to fix this."));
                    }

                    JStringBuilder* builder=new JStringBuilder();
                    JString* systemId = e->getSystemId();
                    if (systemId == null) {
                        systemId = new JString("null");
                    }
                    builder->append(new JString("Error: URI="))
                           ->append(systemId)
                           ->append(new JString(" Line="))
                           ->append(e->getLineNumber())->append(':')->append(e->getMessage());
                    JSystem::err->println(builder->toString());
                    e->printStackTrace();
                    errorCount++;
                }

                JDefaultValidationErrorHandler::~JDefaultValidationErrorHandler(){
                }
            }
        }
    }
}
