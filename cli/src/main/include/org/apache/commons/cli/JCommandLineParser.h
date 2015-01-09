#ifndef JORG_APACHE_COMMONS_CLI_COMMAND_LINE_PARSER_H
#define JORG_APACHE_COMMONS_CLI_COMMAND_LINE_PARSER_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "org/apache/commons/cli/JCommandLine.h"
#include "org/apache/commons/cli/JOptions.h"

using namespace jcpp::lang;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.CommandLineParser", simpleName="CommandLineParser");
                class JCPP_EXPORT JCommandLineParser : public JInterface{
                    public:
                        static JClass* getClazz();

                        virtual JCommandLine* parse(JOptions* options,JPrimitiveObjectArray* arguments)=0;

                        virtual JCommandLine* parse(JOptions* options,JPrimitiveObjectArray* arguments,jbool stopAtNonOption)=0;

                        virtual ~JCommandLineParser();
                };
            }
        }
    }
}
#endif
