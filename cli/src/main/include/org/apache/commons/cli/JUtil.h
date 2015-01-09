#ifndef JORG_APACHE_COMMONS_CLI_UTIL_H
#define JORG_APACHE_COMMONS_CLI_UTIL_H

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
            	// @Class(canonicalName="org.apache.commons.cli.Util", simpleName="Util");
                class JCPP_EXPORT JUtil : public JObject{
                    public:

                        static JClass* getClazz();

                        static JString* stripLeadingHyphens(JString* str);
                        
                        static JString* stripLeadingAndTrailingQuotes(JString* str);

                        virtual ~JUtil();
                };
            }
        }
    }
}
#endif
