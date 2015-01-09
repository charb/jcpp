#include "org/apache/commons/cli/JTypeHandler.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JStringBuilder.h"
#include "org/apache/commons/cli/JAlreadySelectedException.h"
#include "org/apache/commons/cli/JPatternOptionBuilder.h"

using namespace jcpp::io;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                JObject* JTypeHandler::createValue(JString* str, JObject* obj){
                    return createValue(str, dynamic_cast<JClass*>(obj));
                }

                JObject* JTypeHandler::createValue(JString* str, JClass* clazz){
                    if (JPatternOptionBuilder::STRING_VALUE == clazz){
                        return str;

                    }else if (JPatternOptionBuilder::OBJECT_VALUE == clazz){
                        return createObject(str);

                    }else if (JPatternOptionBuilder::NUMBER_VALUE == clazz){
                        return createNumber(str);

                    }else if (JPatternOptionBuilder::CLASS_VALUE == clazz){
                        return createClass(str);

                    }else if (JPatternOptionBuilder::FILE_VALUE == clazz){
                        return createFile(str);

                    }else if (JPatternOptionBuilder::EXISTING_FILE_VALUE == clazz){
                        return createFile(str);

                    }else{
                        return null;
                    }
                }

                JObject* JTypeHandler::createObject(JString* classname){
                    JClass* cl= JClass::forName(classname); 
                    return cl->newInstance();
                }

                JNumber* JTypeHandler::createNumber(JString* str){
                    if (str->indexOf('.') != -1){
                        return JDouble::valueOf(str);
                    }else{
                        return JLong::valueOf(str);
                    }
                }

                JClass* JTypeHandler::createClass(JString* classname){
                    return JClass::forName(classname);
                }

                JFile* JTypeHandler::createFile(JString* str){
                    return new JFile(str);
                }

                JTypeHandler::~JTypeHandler(){
                }
            }
        }
    }
}

