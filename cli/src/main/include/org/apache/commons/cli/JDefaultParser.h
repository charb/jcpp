#ifndef JORG_APACHE_COMMONS_CLI_DEFAULT_PARSER_H
#define JORG_APACHE_COMMONS_CLI_DEFAULT_PARSER_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "org/apache/commons/cli/JCommandLine.h"
#include "org/apache/commons/cli/JCommandLineParser.h"
#include "org/apache/commons/cli/JOptions.h"

using namespace jcpp::lang;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.DefaultParser", simpleName="DefaultParser");
                class JCPP_EXPORT JDefaultParser : public JObject, public JCommandLineParser{
                    protected:
                        JCommandLine* cmd;
                        JOptions* options;
                        jbool stopAtNonOption;
                        JString* currentToken;
                        JOption* currentOption;
                        jbool skipParsing;
                        JList* expectedOpts;

                        void handleProperties(JMap* properties);
                        void checkRequiredOptions();
                        void checkRequiredArgs();
                        void handleToken(JString* token);
                        jbool isArgument(JString* token);
                        jbool isNegativeNumber(JString* token);
                        jbool isOption(JString* token);
                        jbool isShortOption(JString* token);
                        jbool isLongOption(JString* token);
                        void handleUnknownToken(JString* token);
                        void handleLongOption(JString* token);
                        void handleLongOptionWithoutEqual(JString* token);
                        void handleLongOptionWithEqual(JString* token);
                        void handleShortAndLongOption(JString* token);
                        JString* getLongPrefix(JString* token);
                        jbool isJavaProperty(JString* token);
                        void handleOption(JOption* option);
                        void updateRequiredOptions(JOption* option);
                        void handleConcatenatedOptions(JString* token);

                    public:
                        JDefaultParser();

                        static JClass* getClazz();

                        virtual JCommandLine* parse(JOptions* options,JPrimitiveObjectArray* arguments);

                        virtual JCommandLine* parse(JOptions* options,JPrimitiveObjectArray* arguments,JMap* properties);

                        virtual JCommandLine* parse(JOptions* options,JPrimitiveObjectArray* arguments,jbool stopAtNonOption);

                        virtual JCommandLine* parse(JOptions* options,JPrimitiveObjectArray* arguments,JMap* properties,jbool stopAtNonOption);

                        virtual ~JDefaultParser();
                };
            }
        }
    }
}
#endif
