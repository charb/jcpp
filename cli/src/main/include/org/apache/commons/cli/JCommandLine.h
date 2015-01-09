#ifndef JORG_APACHE_COMMONS_CLI_COMMAND_LINE_H
#define JORG_APACHE_COMMONS_CLI_COMMAND_LINE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JCollection.h"
#include "org/apache/commons/cli/JOption.h"

using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::util;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.CommandLine", simpleName="CommandLine");
                class JCPP_EXPORT JCommandLine : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = 1LL;
                	protected:
                        JList* args;
                        JList* options;

                        JCommandLine(JClass* _class);
                        virtual JOption* resolveOption(JString* o);
                        virtual void addArg(JString* arg);
                        virtual void addOption(JOption* o);
                        friend class JDefaultParser;

                    public:
                        JCommandLine();

                        static JClass* getClazz();

                        virtual jbool hasOption(JString* o);

                        virtual jbool hasOption(jchar c);

                        virtual JObject* getOptionObject(JString* opt);

                        virtual JObject* getParsedOptionValue(JString* opt);

                        virtual JObject* getOptionObject(jchar o);

                        virtual JString* getOptionValue(JString* o);

                        virtual JString* getOptionValue(jchar c);

                        virtual JPrimitiveObjectArray* getOptionValues(JString* o);

                        virtual JPrimitiveObjectArray* getOptionValues(jchar o);

                        virtual JString* getOptionValue(JString* o,JString* d);

                        virtual JString* getOptionValue(jchar c,JString* d);

                        virtual JMap* getOptionProperties(JString* opt);

                        virtual JPrimitiveObjectArray* getArgs();

                        virtual JList* getArgList();

                        virtual JIterator* iterator();

                        virtual JPrimitiveObjectArray* getOptions();

                        virtual ~JCommandLine();
                };
            }
        }
    }
}
#endif
