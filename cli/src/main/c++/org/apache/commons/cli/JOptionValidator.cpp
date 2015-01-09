#include "org/apache/commons/cli/JOptionValidator.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JStringBuilder.h"
#include "org/apache/commons/cli/JAlreadySelectedException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                void JOptionValidator::validateOption(JString* opt){
                    if (opt == null){
                        return;
                    }
                    
                    if (opt->length() == 1){
                        jchar ch = opt->charAt(0);
                        if (!isValidOpt(ch)){
                            JStringBuilder* buf=new JStringBuilder();
                            buf->append(new JString("Illegal option name '"));
                            buf->append(ch);
                            buf->append('\'');
                            throw new JIllegalArgumentException(buf->toString());
                        }

                    }else{
                        JPrimitiveCharArray* a=opt->toCharArray();
                        for (jint i=0;i<a->size();i++){
                            jchar ch =a->getChar(i);
                            if (!isValidChar(ch)){
                                JStringBuilder* buf=new JStringBuilder();
                                buf->append(new JString("The option '"));
                                buf->append(opt);
                                buf->append("' contains an illegal character : '");
                                buf->append(ch);
                                buf->append('\'');
                                throw new JIllegalArgumentException(buf->toString());
                            }
                        }
                    }
                }

                jbool JOptionValidator::isValidOpt(jchar c){
                    return isValidChar(c) || c == '?' || c == '@';
                }

                jbool JOptionValidator::isValidChar(jchar c){
                    return JCharacter::isJavaIdentifierPart(c);
                }

                JOptionValidator::~JOptionValidator(){
                }
            }
        }
    }
}

