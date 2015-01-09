#ifndef JORG_APACHE_COMMONS_CLI_UNRECOGNIZED_OPTION_EXCEPTION_H
#define JORG_APACHE_COMMONS_CLI_UNRECOGNIZED_OPTION_EXCEPTION_H

#include "jcpp/lang/JObject.h"
#include "org/apache/commons/cli/JParseException.h"

using namespace jcpp::lang;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.UnrecognizedOptionException", simpleName="UnrecognizedOptionException");
                class JCPP_EXPORT JUnrecognizedOptionException : public JParseException{
            		private:
            			static const jlong serialVersionUID = -252504690284625623LL;

                	protected:
                        JString* option;
                		JUnrecognizedOptionException(JClass* _class);

                    public:

                        JUnrecognizedOptionException();

                        JUnrecognizedOptionException(JString* message);

                        JUnrecognizedOptionException(JString* message,JString* option);
                        
                        static JClass* getClazz();

                        virtual JString* getOption();

                        virtual ~JUnrecognizedOptionException();
                };
            }
        }
    }
}
#endif
