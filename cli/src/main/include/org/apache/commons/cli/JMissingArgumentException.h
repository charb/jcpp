#ifndef JORG_APACHE_COMMONS_CLI_MISSING_ARGUMENT_EXCEPTION_H
#define JORG_APACHE_COMMONS_CLI_MISSING_ARGUMENT_EXCEPTION_H

#include "jcpp/lang/JObject.h"
#include "org/apache/commons/cli/JOptionGroup.h"
#include "org/apache/commons/cli/JOption.h"
#include "org/apache/commons/cli/JParseException.h"

using namespace jcpp::lang;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.MissingArgumentException", simpleName="MissingArgumentException");
                class JCPP_EXPORT JMissingArgumentException : public JParseException{
                	private:
                		static const jlong serialVersionUID = -7098538588704965017LL;

                	protected:
                        JOption* option;

                    public:
                        JMissingArgumentException(JString* message);

                        JMissingArgumentException(JOption* option);

                        static JClass* getClazz();

                        virtual JOption* getOption();

                        virtual ~JMissingArgumentException();
                };
            }
        }
    }
}
#endif
