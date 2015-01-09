#include "org/apache/commons/cli/JOptions.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JCollections.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/lang/JStringBuilder.h"
#include "org/apache/commons/cli/JAlreadySelectedException.h"
#include "org/apache/commons/cli/JUtil.h"

using namespace jcpp::util;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JOptions::JOptions():JObject(getClazz()){
                    shortOpts=new JHashMap();
                    longOpts=new JHashMap();
                    requiredOpts=new JArrayList();
                    optionGroups=new JHashMap();
                }

                JOptions* JOptions::addOptionGroup(JOptionGroup* group){
                    if (group->isRequired()){
                        requiredOpts->add(group);
                    }

                    JIterator* it=group->getOptions()->iterator();
                    while (it->hasNext()){
                        JOption* option = dynamic_cast<JOption*>(it->next());
                        option->setRequired(false);
                        addOption(option);
                        optionGroups->put(option->getKey(), group);
                    }
                    return this;
                }

                JCollection* JOptions::getOptionGroups(){
                    return optionGroups->values();
                }

                JOptions* JOptions::addOption(JString* opt, JString* description){
                    addOption(opt, null, false, description);
                    return this;
                }

                JOptions* JOptions::addOption(JString* opt, jbool hasArg, JString* description){
                    addOption(opt, null, hasArg, description);
                    return this;
                }

                JOptions* JOptions::addOption(JString* opt, JString* longOpt, jbool hasArg, JString* description){
                    addOption(new JOption(opt, longOpt, hasArg, description));
                    return this;
                }

                JOptions* JOptions::addOption(JOption* opt){
                    JString* key = opt->getKey();

                    if (opt->hasLongOpt()){
                        longOpts->put(opt->getLongOpt(), opt);
                    }

                    if (opt->isRequired()){
                        if (requiredOpts->contains(key)){
                            requiredOpts->remove(requiredOpts->indexOf(key));
                        }
                        requiredOpts->add(key);
                    }
                    shortOpts->put(key, opt);
                    return this;
                }

                JCollection* JOptions::getOptions(){
                    return JCollections::unmodifiableCollection(helpOptions());
                }

                JList* JOptions::helpOptions(){
                    return new JArrayList(shortOpts->values());
                }

                JList* JOptions::getRequiredOptions(){
                    return JCollections::unmodifiableList(requiredOpts);
                }

                JOption* JOptions::getOption(JString* opt){
                    opt = JUtil::stripLeadingHyphens(opt);

                    if (shortOpts->containsKey(opt)){
                        return dynamic_cast<JOption*>(shortOpts->get(opt));
                    }

                    return dynamic_cast<JOption*>(longOpts->get(opt));
                }

                JList* JOptions::getMatchingOptions(JString* opt){
                    opt = JUtil::stripLeadingHyphens(opt);
                    
                    JList* matchingOpts = new JArrayList();
                    
                    JIterator* it=longOpts->keySet()->iterator();
                    while (it->hasNext()){
                        JString* longOpt=dynamic_cast<JString*>(it->next());
                        if (longOpt->startsWith(opt)){
                            matchingOpts->add(longOpt);
                        }
                    }
                    return matchingOpts;
                }

                jbool JOptions::hasOption(JString* opt){
                    opt = JUtil::stripLeadingHyphens(opt);
                    return shortOpts->containsKey(opt) || longOpts->containsKey(opt);
                }

                jbool JOptions::hasLongOption(JString* opt){
                    opt = JUtil::stripLeadingHyphens(opt);
                    return longOpts->containsKey(opt);
                }

                jbool JOptions::hasShortOption(JString* opt){
                    opt = JUtil::stripLeadingHyphens(opt);
                    return shortOpts->containsKey(opt);
                }

                JOptionGroup* JOptions::getOptionGroup(JOption* opt){
                    return dynamic_cast<JOptionGroup*>(optionGroups->get(opt->getKey()));
                }

                JString* JOptions::toString(){
                    JStringBuilder* buf = new JStringBuilder();
                    buf->append(new JString("[ Options: [ short "));
                    buf->append(dynamic_cast<JObject*>(shortOpts)->toString());
                    buf->append(new JString(" ] [ long "));
                    buf->append(longOpts);
                    buf->append(new JString(" ]"));
                    return buf->toString();
                }

                JOptions::~JOptions(){
                }
            }
        }
    }
}

