#include "org/apache/commons/cli/JPatternOptionBuilder.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/io/JFileInputStream.h"
#include "jcpp/io/JFile.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JStringBuilder.h"
#include "org/apache/commons/cli/JAlreadySelectedException.h"

using namespace jcpp::io;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JClass* JPatternOptionBuilder::STRING_VALUE = JString::getClazz();

                JClass* JPatternOptionBuilder::OBJECT_VALUE = JObject::getClazz();

                JClass* JPatternOptionBuilder::NUMBER_VALUE = JNumber::getClazz();

                JClass* JPatternOptionBuilder::CLASS_VALUE = JClass::getClazz();

                JClass* JPatternOptionBuilder::EXISTING_FILE_VALUE = JFileInputStream::getClazz();

                JClass* JPatternOptionBuilder::FILE_VALUE = JFile::getClazz();

                JClass* JPatternOptionBuilder::FILES_VALUE = JPrimitiveObjectArray::getClazz(JFile::getClazz());

                JObject* JPatternOptionBuilder::getValueClass(jchar ch){
                    switch (ch){
                        case '@':
                            return JPatternOptionBuilder::OBJECT_VALUE;
                        case ':':
                            return JPatternOptionBuilder::STRING_VALUE;
                        case '%':
                            return JPatternOptionBuilder::NUMBER_VALUE;
                        case '+':
                            return JPatternOptionBuilder::CLASS_VALUE;
                        case '<':
                            return JPatternOptionBuilder::EXISTING_FILE_VALUE;
                        case '>':
                            return JPatternOptionBuilder::FILE_VALUE;
                    }

                    return null;
                }

                jbool JPatternOptionBuilder::isValueCode(jchar ch){
                    return ch == '@'
                            || ch == ':'
                            || ch == '%'
                            || ch == '+'
                            || ch == '#'
                            || ch == '<'
                            || ch == '>'
                            || ch == '*'
                            || ch == '/'
                            || ch == '!';
                }

                JOptions* JPatternOptionBuilder::parsePattern(JString* pattern){
                    jchar opt = ' ';
                    jbool required = false;
                    JClass* type = null;

                    JOptions* options = new JOptions();

                    for (jint i = 0; i < pattern->length(); i++){
                        jchar ch = pattern->charAt(i);

                        if (!isValueCode(ch)){
                            if (opt != ' '){
                                JOption* option = JOption::builder(JString::valueOf(opt))
                                    ->hasArg(type != null)
                                    ->required(required)
                                    ->type(type)
                                    ->build();
                                
                                options->addOption(option);
                                required = false;
                                type = null;
                                opt = ' ';
                            }

                            opt = ch;

                        }else if (ch == '!'){
                            required = true;
                        }else{
                            type = dynamic_cast<JClass*>(getValueClass(ch));
                        }
                    }

                    if (opt != ' '){
                        JOption* option = JOption::builder(JString::valueOf(opt))
                            ->hasArg(type != null)
                            ->required(required)
                            ->type(type)
                            ->build();
                        options->addOption(option);
                    }
                    return options;
                }

                JPatternOptionBuilder::~JPatternOptionBuilder(){
                }
            }
        }
    }
}

