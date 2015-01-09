#ifndef JORG_APACHE_COMMONS_CLI_ALREADY_SELECTED_EXCEPTION_H
#define JORG_APACHE_COMMONS_CLI_ALREADY_SELECTED_EXCEPTION_H

#include "jcpp/lang/JObject.h"
#include "org/apache/commons/cli/JOptionGroup.h"
#include "org/apache/commons/cli/JOption.h"
#include "org/apache/commons/cli/JParseException.h"

using namespace jcpp::lang;

//TODO most of classes in cli are serializable, their classes should be changed accordingly ...
namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

            	// @Class(canonicalName="org.apache.commons.cli.AlreadySelectedException", simpleName="AlreadySelectedException");
                class JCPP_EXPORT JAlreadySelectedException : public JParseException{
                	private:
                		static const jlong serialVersionUID = 3674381532418544760LL;

                	protected:
                        JOptionGroup* group;
                        JOption* option;

                    public:
                        JAlreadySelectedException(JString* message);

                        JAlreadySelectedException(JOptionGroup* group,JOption* option);

                        static JClass* getClazz();

                        virtual JOptionGroup* getOptionGroup();

                        virtual JOption* getOption();

                        virtual ~JAlreadySelectedException();
                };
            }
        }
    }
}
#endif
