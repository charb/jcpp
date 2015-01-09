#include "org/apache/commons/cli/JUtil.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JStringBuilder.h"
#include "org/apache/commons/cli/JAlreadySelectedException.h"

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JString* JUtil::stripLeadingHyphens(JString* str){
                    if (str == null){
                        return null;
                    }
                    if (str->startsWith(new JString("--"))){
                        return str->substring(2, str->length());

                    }else if (str->startsWith(new JString("-"))){
                        return str->substring(1, str->length());
                    }
                    return str;
                }

                JString* JUtil::stripLeadingAndTrailingQuotes(JString* str){
                    jint length = str->length();
                    if (length > 1 && str->startsWith(new JString("\"")) && 
                        str->endsWith(new JString("\"")) && 
                        str->substring(1, length - 1)->indexOf(new JString("\"")) == -1){
                        str = str->substring(1, length - 1);
                    }
                    return str;
                }

                JUtil::~JUtil(){
                }
            }
        }
    }
}

