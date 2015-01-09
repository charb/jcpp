#include "org/apache/commons/cli/JCommandLine.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JStringBuilder.h"
#include "org/apache/commons/cli/JAlreadySelectedException.h"
#include "org/apache/commons/cli/JTypeHandler.h"
#include "org/apache/commons/cli/JUtil.h"

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JCommandLine::JCommandLine(JClass* _class):JObject(_class){
                    args=new JArrayList();
                    options=new JArrayList();
                }

                JCommandLine::JCommandLine():JObject(getClazz()){
                    args=new JArrayList();
                    options=new JArrayList();
                }

                jbool JCommandLine::hasOption(JString* o){
                    return options->contains(resolveOption(o));
                }

                jbool JCommandLine::hasOption(jchar c){
                    return hasOption(JString::valueOf(c));
                }
                
                JObject* JCommandLine::getOptionObject(JString* opt){
                    return getParsedOptionValue(opt);
                }

                JObject* JCommandLine::getParsedOptionValue(JString* opt){
                    JString* res=getOptionValue(opt);
                    JOption* option=resolveOption(opt);
                    if (option==null || res==null){
                        return null;
                    }
                    return JTypeHandler::createValue(res,option->getType());
                }

                JObject* JCommandLine::getOptionObject(jchar o){
                    return getOptionObject(JString::valueOf(o));
                }

                JString* JCommandLine::getOptionValue(JString* o){
                    JPrimitiveObjectArray* values=getOptionValues(o);
                    return (values ==null ? null : dynamic_cast<JString*>(values->get(0)));
                }

                JString* JCommandLine::getOptionValue(jchar c){
                    return getOptionValue(JString::valueOf(c));
                }

                JPrimitiveObjectArray* JCommandLine::getOptionValues(JString* o){
                    JList* values = new JArrayList();
                    for (jint i=0;i<options->size();i++){
                        JOption* option=dynamic_cast<JOption*>(options->get(i));
                        if (o->equals(option->getOpt()) || o->equals(option->getLongOpt())){
                            values->addAll(option->getValuesList());
                        }
                    }
                    return values->isEmpty() ? null : dynamic_cast<JPrimitiveObjectArray*>(values->toArray(new JPrimitiveObjectArray(JString::getClazz(), values->size())));
                }

                JOption* JCommandLine::resolveOption(JString* o){
                    o = JUtil::stripLeadingHyphens(o);
                    for (jint i=0;i<options->size();i++){
                        JOption* option=dynamic_cast<JOption*>(options->get(i));
                        if (o->equals(option->getOpt())){
                            return option;
                        }

                        if (o->equals(option->getLongOpt())){
                            return option;
                        }
                    }
                    return null;
                }

                JPrimitiveObjectArray* JCommandLine::getOptionValues(jchar o){
                    return getOptionValues(JString::valueOf(o));
                }

                JString* JCommandLine::getOptionValue(JString* o,JString* d){
                    JString* answer = getOptionValue(o);
                    return (answer != null) ? answer : d;
                }

                JString* JCommandLine::getOptionValue(jchar c,JString* d){
                    return getOptionValue(JString::valueOf(c), d);
                }

                JMap* JCommandLine::getOptionProperties(JString* opt){
                    JMap* props = new JHashMap();

                    for (jint i=0;i<options->size();i++){
                        JOption* option=dynamic_cast<JOption*>(options->get(i));
                        if (opt->equals(option->getOpt()) || opt->equals(option->getLongOpt())){
                            JList* values = option->getValuesList();
                            if (values->size() >= 2){
                                props->put(dynamic_cast<JObject*>(values->get(0)), dynamic_cast<JObject*>(values->get(1)));

                            }else if (values->size() == 1){
                                props->put(dynamic_cast<JObject*>(values->get(0)), new JString("true"));
                            }
                        }
                    }
                    return props;
                }

                JPrimitiveObjectArray* JCommandLine::getArgs(){
                    JPrimitiveObjectArray* answer = new JPrimitiveObjectArray(JString::getClazz(),args->size());
                    args->toArray(answer);
                    return answer;
                }

                JList* JCommandLine::getArgList(){
                    return args;
                }

                void JCommandLine::addArg(JString* arg){
                    args->add(arg);
                }

                void JCommandLine::addOption(JOption* o){
                    options->add(o);
                }

                JIterator* JCommandLine::iterator(){
                    return options->iterator();
                }

                JPrimitiveObjectArray* JCommandLine::getOptions(){
                    JCollection* processed = options;

                    JPrimitiveObjectArray* optionsArray = new JPrimitiveObjectArray(JOption::getClazz(),processed->size());
                    return dynamic_cast<JPrimitiveObjectArray*>(processed->toArray(optionsArray));
                }

                JCommandLine::~JCommandLine(){
                }
            }
        }
    }
}

