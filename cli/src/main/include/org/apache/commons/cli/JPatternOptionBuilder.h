#ifndef JORG_APACHE_COMMONS_CLI_PATTERN_OPTION_BUILDER_H
#define JORG_APACHE_COMMONS_CLI_PATTERN_OPTION_BUILDER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JCollection.h"
#include "org/apache/commons/cli/JOption.h"
#include "org/apache/commons/cli/JOptions.h"

using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::util;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.PatternOptionBuilder", simpleName="PatternOptionBuilder");
                class JCPP_EXPORT JPatternOptionBuilder : public JObject{
                	private:
                		static const jlong serialVersionUID = 1LL;

                    public:

                        static JClass* getClazz();

                        static JClass* STRING_VALUE;

                        static JClass* OBJECT_VALUE;

                        static JClass* NUMBER_VALUE;

                        static JClass* CLASS_VALUE;

                        static JClass* EXISTING_FILE_VALUE;

                        static JClass* FILE_VALUE;

                        static JClass* FILES_VALUE;

                        static JObject* getValueClass(jchar ch);
                        
                        static jbool isValueCode(jchar ch);
                        
                        static JOptions* parsePattern(JString* pattern);

                        virtual ~JPatternOptionBuilder();
                };
            }
        }
    }
}
#endif
