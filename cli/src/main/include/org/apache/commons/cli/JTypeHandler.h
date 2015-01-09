#ifndef JORG_APACHE_COMMONS_CLI_TYPE_HANDLER_H
#define JORG_APACHE_COMMONS_CLI_TYPE_HANDLER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JCollection.h"
#include "org/apache/commons/cli/JOption.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/io/JFile.h"

using namespace jcpp::lang;
using namespace jcpp::io;
using namespace jcpp::util;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.TypeHandler", simpleName="TypeHandler");
                class JCPP_EXPORT JTypeHandler : public JObject{
                    public:

                        static JClass* getClazz();

                        static JObject* createValue(JString* str, JObject* obj);

                        static JObject* createValue(JString* str, JClass* clazz);
                        
                        static JObject* createObject(JString* classname);       

                        static JNumber* createNumber(JString* str);

                        static JClass* createClass(JString* classname);

                        static JFile* createFile(JString* str);

                        virtual ~JTypeHandler();
                };
            }
        }
    }
}
#endif
