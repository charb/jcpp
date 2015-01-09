#ifndef JORG_APACHE_COMMONS_CLI_AMBIGUOUS_OPTION_EXCEPTION_H
#define JORG_APACHE_COMMONS_CLI_AMBIGUOUS_OPTION_EXCEPTION_H

#include "jcpp/lang/JObject.h"
#include "org/apache/commons/cli/JUnrecognizedOptionException.h"
#include "jcpp/util/JCollection.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.AmbiguousOptionException", simpleName="AmbiguousOptionException");
                class JCPP_EXPORT JAmbiguousOptionException : public JUnrecognizedOptionException{
                	private:
                		static const jlong serialVersionUID = 5829816121277947229LL;
                	protected:
                        JCollection* matchingOptions;
                        static JString* createMessage(JString* o,JCollection* mo);

                    public:
                        JAmbiguousOptionException(JString* o, JCollection* mo);
                        
                        static JClass* getClazz();

                        virtual JCollection* getMatchingOptions();

                        virtual ~JAmbiguousOptionException();
                };
            }
        }
    }
}
#endif
