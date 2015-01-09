#include "org/apache/commons/cli/JDefaultParser.h"
#include "org/apache/commons/cli/JUnrecognizedOptionException.h"
#include "org/apache/commons/cli/JMissingOptionException.h"
#include "org/apache/commons/cli/JMissingArgumentException.h"
#include "org/apache/commons/cli/JAmbiguousOptionException.h"
#include "org/apache/commons/cli/JUtil.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JNumberFormatException.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JEnumeration.h"

using namespace jcpp::util;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JDefaultParser::JDefaultParser():JObject(getClazz()){
                    cmd=null;
                    options=null;
                    stopAtNonOption=false;
                    currentToken=null;
                    currentOption=null;
                    skipParsing=false;
                    expectedOpts=null;  
                }

                JCommandLine* JDefaultParser::parse(JOptions* options, JPrimitiveObjectArray* arguments){
                    return JDefaultParser::parse(options, arguments, (JMap*)null);
                }

                JCommandLine* JDefaultParser::parse(JOptions* options, JPrimitiveObjectArray* arguments, JMap* properties){
                    return JDefaultParser::parse(options, arguments, properties, false);
                }

                JCommandLine* JDefaultParser::parse(JOptions* options, JPrimitiveObjectArray* arguments, jbool stopAtNonOption){
                    return JDefaultParser::parse(options, arguments, null, stopAtNonOption);
                }

                JCommandLine* JDefaultParser::parse(JOptions* options, JPrimitiveObjectArray* arguments, JMap* properties, jbool stopAtNonOption){
                    this->options = options;
                    this->stopAtNonOption = stopAtNonOption;
                    skipParsing = false;
                    currentOption = null;
                    expectedOpts = new JArrayList(options->getRequiredOptions());

                    JIterator* it=options->getOptionGroups()->iterator();
                    while (it->hasNext()){
                        JOptionGroup* group = dynamic_cast<JOptionGroup*>(it->next());
                        group->setSelected(null);
                    }
                    cmd = new JCommandLine();
                    if (arguments != null){
                        for (jint i=0;i<arguments->size();i++){
                            JString* argument= dynamic_cast<JString*>(arguments->get(i));
                            handleToken(argument);
                        }
                    }
                    checkRequiredArgs();
                    handleProperties(properties);
                    checkRequiredOptions();

                    return cmd;
                }

                void JDefaultParser::handleProperties(JMap* properties){
                    if (properties == null){
                        return;
                    }

                    for (JIterator* e = properties->keySet()->iterator(); e->hasNext();){
                        JString* option = e->next()->toString();
                        JOption* opt = options->getOption(option);
                        if (opt == null){
                            throw new JUnrecognizedOptionException(new JString("Default option wasn't defined"), option);
                        }

                        JOptionGroup* group = options->getOptionGroup(opt);
                        jbool selected = group != null && group->getSelected() != null;

                        if (!cmd->hasOption(option) && !selected){
                            JString* value = dynamic_cast<JString*>(properties->get(option));

                            if (opt->hasArg()){
                                if (opt->getValues() == null || opt->getValues()->size() == 0){
                                    opt->addValueForProcessing(value);
                                }

                            }else if (!((new JString("yes"))->equalsIgnoreCase(value) || (new JString("true"))->equalsIgnoreCase(value)
                                     || (new JString("1"))->equalsIgnoreCase(value))) {
                                continue;
                            }

                            handleOption(opt);
                            currentOption = null;
                        }
                    }
                }

                void JDefaultParser::checkRequiredOptions(){
                    if (!expectedOpts->isEmpty()){
                        throw new JMissingOptionException(expectedOpts);
                    }
                }

                void JDefaultParser::checkRequiredArgs(){
                    if (currentOption != null && currentOption->requiresArg()){
                        throw new JMissingArgumentException(currentOption);
                    }
                }

                void JDefaultParser::handleToken(JString* token){
                    currentToken = token;

                    if (skipParsing){
                        cmd->addArg(token);

                    }else if ((new JString("--"))->equals(token)){
                        skipParsing = true;

                    }else if (currentOption != null && currentOption->acceptsArg() && isArgument(token)){
                        currentOption->addValueForProcessing(JUtil::stripLeadingAndTrailingQuotes(token));

                    }else if (token->startsWith(new JString("--"))){
                        handleLongOption(token);

                    }else if (token->startsWith(new JString("-")) && !(new JString("-"))->equals(token)){
                        handleShortAndLongOption(token);

                    }else{
                        handleUnknownToken(token);
                    }

                    if (currentOption != null && !currentOption->acceptsArg()){
                        currentOption = null;
                    }
                }

                jbool JDefaultParser::isArgument(JString* token){
                    return !isOption(token) || isNegativeNumber(token);
                }

                jbool JDefaultParser::isNegativeNumber(JString* token){
                    try{
                        JDouble::parseDouble(token);
                        return true;
                    }catch (JNumberFormatException* e){
                        return false;
                    }
                }

                jbool JDefaultParser::isOption(JString* token){
                    return isLongOption(token) || isShortOption(token);
                }

                jbool JDefaultParser::isShortOption(JString* token){
                    jbool b=token->startsWith(new JString("-")) && token->length() >= 2 && options->hasShortOption(token->substring(1, 2));
                    return b;
                }

                jbool JDefaultParser::isLongOption(JString* token){
                    if (!token->startsWith(new JString("-")) || token->length() == 1){
                        return false;
                    }

                    jint pos = token->indexOf(new JString("="));
                    JString* t = pos == -1 ? token : token->substring(0, pos);

                    if (!options->getMatchingOptions(t)->isEmpty()){
                        return true;

                    }else if (getLongPrefix(token) != null && !token->startsWith(new JString("--"))){
                        return true;
                    }

                    return false;
                }

                void JDefaultParser::handleUnknownToken(JString* token){
                    if (token->startsWith(new JString("-")) && token->length() > 1 && !stopAtNonOption){
                        JStringBuffer* buf=new JStringBuffer();
                        buf->append(new JString("Unrecognized option: "));
                        buf->append(token);
                        throw new JUnrecognizedOptionException(buf->toString(), token);
                    }

                    cmd->addArg(token);
                    if (stopAtNonOption){
                        skipParsing = true;
                    }
                }

                void JDefaultParser::handleLongOption(JString* token){
                    if (token->indexOf(new JString("=")) == -1){
                        handleLongOptionWithoutEqual(token);
                    }else{
                        handleLongOptionWithEqual(token);
                    }
                }
                
                void JDefaultParser::handleLongOptionWithoutEqual(JString* token){
                    JList* matchingOpts = options->getMatchingOptions(token);
                    if (matchingOpts->isEmpty()){
                        handleUnknownToken(currentToken);

                    }else if (matchingOpts->size() > 1){
                        throw new JAmbiguousOptionException(token, matchingOpts);
                    }else{
                        handleOption(options->getOption(dynamic_cast<JString*>(matchingOpts->get(0))));
                    }
                }

                void JDefaultParser::handleLongOptionWithEqual(JString* token){
                    jint pos = token->indexOf(new JString("="));

                    JString* value = token->substring(pos + 1);

                    JString* opt = token->substring(0, pos);

                    JList* matchingOpts = options->getMatchingOptions(opt);
                    if (matchingOpts->isEmpty()){
                        handleUnknownToken(currentToken);

                    }else if (matchingOpts->size() > 1){
                        throw new JAmbiguousOptionException(opt, matchingOpts);
                    }else{
                        JOption* option = options->getOption(dynamic_cast<JString*>(matchingOpts->get(0)));
                        if (option->acceptsArg()){
                            handleOption(option);
                            currentOption->addValueForProcessing(value);
                            currentOption = null;
                        }else{
                            handleUnknownToken(currentToken);
                        }
                    }
                }

                void JDefaultParser::handleShortAndLongOption(JString* token){
                    JString* t = JUtil::stripLeadingHyphens(token);

                    jint pos = t->indexOf(new JString("="));

                    if (t->length() == 1){
                        if (options->hasShortOption(t)){
                            handleOption(options->getOption(t));
                        }else{
                            handleUnknownToken(token);
                        }
                    }else if (pos == -1){
                        if (options->hasShortOption(t)){
                            handleOption(options->getOption(t));

                        }else if (!options->getMatchingOptions(t)->isEmpty()){
                            handleLongOptionWithoutEqual(token);
                        }else{
                            JString* opt = getLongPrefix(t);
                            if (opt != null && options->getOption(opt)->acceptsArg()){
                                handleOption(options->getOption(opt));
                                currentOption->addValueForProcessing(t->substring(opt->length()));
                                currentOption = null;
                            }else if (isJavaProperty(t)){
                                handleOption(options->getOption(t->substring(0, 1)));
                                currentOption->addValueForProcessing(t->substring(1));
                                currentOption = null;
                            }else{
                                handleConcatenatedOptions(token);
                            }
                        }
                    }else{
                        JString* opt = t->substring(0, pos);
                        JString* value = t->substring(pos + 1);

                        if (opt->length() == 1){
                            JOption* option = options->getOption(opt);
                            if (option != null && option->acceptsArg()){
                                handleOption(option);
                                currentOption->addValueForProcessing(value);
                                currentOption = null;
                            }else{
                                handleUnknownToken(token);
                            }
                        }else if (isJavaProperty(opt)){
                            handleOption(options->getOption(opt->substring(0, 1)));
                            currentOption->addValueForProcessing(opt->substring(1));
                            currentOption->addValueForProcessing(value);
                            currentOption = null;
                        }else{
                            handleLongOptionWithEqual(token);
                        }
                    }
                }

                JString* JDefaultParser::getLongPrefix(JString* token){
                    JString* t = JUtil::stripLeadingHyphens(token);

                    jint i;
                    JString* opt = null;
                    for (i = t->length() - 2; i > 1; i--){
                        JString* prefix = t->substring(0, i);
                        if (options->hasLongOption(prefix)){
                            opt = prefix;
                            break;
                        }
                    }
                    
                    return opt;
                }

                jbool JDefaultParser::isJavaProperty(JString* token){
                    JString* opt = token->substring(0, 1);
                    JOption* option = options->getOption(opt);

                    return option != null && (option->getArgs() >= 2 || option->getArgs() == JOption::UNLIMITED_VALUES);
                }

                void JDefaultParser::handleOption(JOption* option){
                    checkRequiredArgs();
                    option = dynamic_cast<JOption*>(option->clone());
                    updateRequiredOptions(option);
                    cmd->addOption(option);
                    if (option->hasArg()){
                        currentOption = option;
                    }else{
                        currentOption = null;
                    }
                }

                void JDefaultParser::updateRequiredOptions(JOption* option){
                    if (option->isRequired()){
                        expectedOpts->remove(option->getKey());
                    }
                    if (options->getOptionGroup(option) != null){
                        JOptionGroup* group = options->getOptionGroup(option);
                        if (group->isRequired()){
                            expectedOpts->remove(group);
                        }
                        group->setSelected(option);
                    }
                }

                void JDefaultParser::handleConcatenatedOptions(JString* token){
                    for (jint i = 1; i < token->length(); i++){
                        JString* ch = JString::valueOf(token->charAt(i));

                        if (options->hasOption(ch)){
                            handleOption(options->getOption(ch));

                            if (currentOption != null && (token->length() != (i + 1))){
                                currentOption->addValueForProcessing(token->substring(i + 1));
                                break;
                            }
                        }else{
                            handleUnknownToken(stopAtNonOption && i > 1 ? token->substring(i) : token);
                            break;
                        }
                    }
                }

                JDefaultParser::~JDefaultParser(){
                }
            }
        }
    }
}

