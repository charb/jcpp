#ifndef JORG_APACHE_COMMONS_CLI_OPTION_VALIDATOR_H
#define JORG_APACHE_COMMONS_CLI_OPTION_VALIDATOR_H

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
            	// @Class(canonicalName="org.apache.commons.cli.OptionValidator", simpleName="OptionValidator");
                class JCPP_EXPORT JOptionValidator : public JObject{
                	private:
                		static const jlong serialVersionUID = 1LL;

                    public:
                        static JClass* getClazz();

                        static void validateOption(JString* opt);

                        static jbool isValidOpt(jchar c);

                        static jbool isValidChar(jchar c);

                        virtual ~JOptionValidator();
                };
            }
        }
    }
}
#endif
