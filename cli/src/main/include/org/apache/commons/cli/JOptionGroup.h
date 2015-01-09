#ifndef JORG_APACHE_COMMONS_CLI_OPTION_GROUP_H
#define JORG_APACHE_COMMONS_CLI_OPTION_GROUP_H

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
            	// @Class(canonicalName="org.apache.commons.cli.OptionGroup", simpleName="OptionGroup");
                class JCPP_EXPORT JOptionGroup : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = 1LL;

                	protected:
                        JMap* optionMap;
                        JString* selected;
                        jbool required;

                    public:
                        JOptionGroup();

                        static JClass* getClazz();

                        virtual JOptionGroup* addOption(JOption* o);

                        virtual JCollection* getNames();

                        virtual JCollection* getOptions();

                        virtual void setSelected(JOption* o);

                        virtual JString* getSelected();

                        virtual void setRequired(jbool r);

                        virtual jbool isRequired();

                        virtual JString* toString();

                        virtual ~JOptionGroup();
                };
            }
        }
    }
}
#endif
