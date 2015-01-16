#include "org/apache/commons/cli/JMissingOptionException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JStringBuilder.h"

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JMissingOptionException::JMissingOptionException(JString* message):JParseException(getClazz()){
                    this->detailMessage=message;
                    missingOptions=null;
                }

                JMissingOptionException::JMissingOptionException(JList* l):JParseException(getClazz()){
                    this->detailMessage=createMessage(l);
                    this->missingOptions=l;
                }

                JList* JMissingOptionException::getMissingOptions(){
                    return missingOptions;
                }

                JString* JMissingOptionException::createMessage(JList* missingOptions){
                    JStringBuilder* buf = new JStringBuilder();
                    buf->append(new JString("Missing required option"));
                    buf->append(missingOptions->size() == 1 ? new JString(" ") : new JString("s"));
                    buf->append(new JString(": "));

                    JIterator* it = missingOptions->iterator();
                    while (it->hasNext()){
                        buf->append(it->next());
                        if (it->hasNext()){
                            buf->append(new JString(", "));
                        }
                    }
                    return buf->toString();
                }

                JMissingOptionException::~JMissingOptionException(){
                }
            }
        }
    }
}
