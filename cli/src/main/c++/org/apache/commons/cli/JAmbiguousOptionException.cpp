#include "org/apache/commons/cli/JAmbiguousOptionException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/util/JIterator.h"

using namespace jcpp::util;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JAmbiguousOptionException::JAmbiguousOptionException(JString* o, JCollection* mo):JUnrecognizedOptionException(getClazz()){
                    this->message=createMessage(o,mo);
                    this->option=o;
                    this->matchingOptions=mo;
                }
                
                JCollection* JAmbiguousOptionException::getMatchingOptions(){
                    return matchingOptions;
                }

                JString* JAmbiguousOptionException::createMessage(JString* o,JCollection* mo){
                    JStringBuilder* buf = new JStringBuilder();
                    buf->append(new JString("Ambiguous option: '"));
                    buf->append(o);
                    buf->append(new JString("'  (could be: "));

                    JIterator* it = mo->iterator();
                    while (it->hasNext()){
                        buf->append('\'');
                        buf->append(it->next());
                        buf->append('\'');
                        if (it->hasNext()){
                            buf->append(new JString(", "));
                        }
                    }
                    buf->append(')');

                    return buf->toString();
                }

                JAmbiguousOptionException::~JAmbiguousOptionException(){
                }
            }
        }
    }
}

