#ifndef JORG_APACHE_COMMONS_CLI_OPTIONS_H
#define JORG_APACHE_COMMONS_CLI_OPTIONS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JList.h"
#include "org/apache/commons/cli/JOption.h"
#include "org/apache/commons/cli/JOptionGroup.h"

using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::util;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.Options", simpleName="Options");
                class JCPP_EXPORT JOptions : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = 1LL;

                	protected:
                        JMap* shortOpts;
                        JMap* longOpts;
                        JList* requiredOpts;
                        JMap* optionGroups;

                    public:
                        JOptions();

                        static JClass* getClazz();

                        virtual JOptions* addOptionGroup(JOptionGroup* g);

                        virtual JCollection* getOptionGroups();

                        virtual JOptions* addOption(JString* opt, JString* description);

                        virtual JOptions* addOption(JString* opt, jbool hasArg, JString* description);

                        virtual JOptions* addOption(JString* opt, JString* longOpt, jbool hasArg, JString* description);

                        virtual JOptions* addOption(JOption* opt);

                        virtual JCollection* getOptions();

                        virtual JList* helpOptions();

                        virtual JList* getRequiredOptions();

                        virtual JOption* getOption(JString* opt);

                        virtual JList* getMatchingOptions(JString* opt);

                        virtual jbool hasOption(JString* opt);

                        virtual jbool hasLongOption(JString* opt);

                        virtual jbool hasShortOption(JString* opt);

                        virtual JOptionGroup* getOptionGroup(JOption* opt);

                        virtual JString* toString();

                        virtual ~JOptions();
                };
            }
        }
    }
}
#endif
