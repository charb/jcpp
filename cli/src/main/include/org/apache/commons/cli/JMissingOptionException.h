#ifndef JORG_APACHE_COMMONS_CLI_MISSING_OPTION_EXCEPTION_H
#define JORG_APACHE_COMMONS_CLI_MISSING_OPTION_EXCEPTION_H

#include "jcpp/lang/JObject.h"
#include "org/apache/commons/cli/JOptionGroup.h"
#include "org/apache/commons/cli/JOption.h"
#include "org/apache/commons/cli/JParseException.h"

using namespace jcpp::lang;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.MissingOptionException", simpleName="MissingOptionException");
                class JCPP_EXPORT JMissingOptionException : public JParseException{
                	private:
                		static const jlong serialVersionUID = 8161889051578563249LL;

                	protected:
                        JList* missingOptions;
                        static JString* createMessage(JList* missingOptions);

                    public:
                        JMissingOptionException(JString* message);

                        JMissingOptionException(JList* missingOptions);

                        static JClass* getClazz();

                        virtual JList* getMissingOptions();

                        virtual ~JMissingOptionException();
                };
            }
        }
    }
}
#endif
