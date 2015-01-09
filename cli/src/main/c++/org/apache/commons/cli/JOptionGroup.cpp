#include "org/apache/commons/cli/JOptionGroup.h"
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

                JOptionGroup::JOptionGroup():JObject(getClazz()){
                    optionMap=new JHashMap();
                    selected=null;
                    required=false;
                }

                JOptionGroup* JOptionGroup::addOption(JOption* o){
                    optionMap->put(o->getKey(),o);
                    return this;
                }

                JCollection* JOptionGroup::getNames(){
                    return optionMap->keySet();
                }

                JCollection* JOptionGroup::getOptions(){
                    return optionMap->values();
                }

                void JOptionGroup::setSelected(JOption* option){
                    if (option == null){
                        selected = null;
                        return;
                    }
                    
                    if (selected == null || selected->equals(option->getKey())){
                        selected = option->getKey();
                    }else{
                        throw new JAlreadySelectedException(this, option);
                    }
                }

                JString* JOptionGroup::getSelected(){
                    return selected;
                }

                void JOptionGroup::setRequired(jbool required){
                    this->required = required;
                }

                jbool JOptionGroup::isRequired(){
                    return required;
                }

                JString* JOptionGroup::toString(){
                    JStringBuilder* buff = new JStringBuilder();
                    JIterator* iter = getOptions()->iterator();

                    buff->append('[');

                    while (iter->hasNext()){
                        JOption* option = dynamic_cast<JOption*>(iter->next());

                        if (option->getOpt() != null){
                            buff->append('-');
                            buff->append(option->getOpt());

                        }else{
                            buff->append(new JString("--"));
                            buff->append(option->getLongOpt());
                        }
                        
                        if (option->getDescription() != null){
                            buff->append(' ');
                            buff->append(option->getDescription());
                        }
                        
                        if (iter->hasNext()){
                            buff->append(", ");
                        }
                    }

                    buff->append("]");

                    return buff->toString();
                }

                JOptionGroup::~JOptionGroup(){
                }
            }
        }
    }
}

