#ifndef JORG_APACHE_COMMONS_CLI_PARSE_EXCEPTION_H
#define JORG_APACHE_COMMONS_CLI_PARSE_EXCEPTION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JException.h"

using namespace jcpp::lang;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.ParseException", simpleName="ParseException");
                class JCPP_EXPORT JParseException : public JException{
                	private:
                		static const jlong serialVersionUID = 9112808380089253192LL;

                	protected:
                		JParseException(JClass* _class);

                    public:
                        static JClass* getClazz();

                        JParseException();

                        JParseException(JString* message);

                        virtual ~JParseException();
                };
            }
        }
    }
}
#endif
