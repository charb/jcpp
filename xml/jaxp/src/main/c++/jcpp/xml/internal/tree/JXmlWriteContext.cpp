#include "jcpp/xml/internal/tree/JXmlWriteContext.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JXmlWriteContext::JXmlWriteContext(JClass* _class, JWriter* out):JObject(_class){
                    writer=out;
                    indentLevel=0;
                    prettyOutput=false;
                }

                JXmlWriteContext::JXmlWriteContext(JClass* _class,JWriter* out,jint level):JObject(_class){
                    writer=out;
                    indentLevel=level;
                    prettyOutput=false;
                }

                JXmlWriteContext::JXmlWriteContext(JWriter* out):JObject(getClazz()){
                    writer=out;
                    indentLevel=0;
                    prettyOutput=false;
                }

                JXmlWriteContext::JXmlWriteContext(JWriter* out,jint level):JObject(getClazz()){
                    writer=out;
                    indentLevel=level;
                    prettyOutput=false;
                }

                JWriter* JXmlWriteContext::getWriter(){
                    return writer;
                }

                jbool JXmlWriteContext::isEntityDeclared(JString* name){
                    return ( (new JString("amp"))->equals (name) || 
                             (new JString("lt"))->equals (name) || 
                             (new JString("gt"))->equals (name) || 
                             (new JString("quot"))->equals (name) || 
                             (new JString("apos"))->equals (name));
                }

                jint JXmlWriteContext::getIndentLevel(){
                    return indentLevel;
                }

                void JXmlWriteContext::setIndentLevel(jint level){
                    indentLevel = level;
                }

                void JXmlWriteContext::printIndent(){
                    jint temp = indentLevel;

                    if (!prettyOutput){
                        return;
                    }

                    writer->write(JSystem::lineSeparator());
                    while (temp-- > 0) {
                        writer->write((jchar)' ');
                    }
                }

                jbool JXmlWriteContext::isPrettyOutput(){
                    return prettyOutput;
                }

                JXmlWriteContext::~JXmlWriteContext(){
                }
            }
        }
    }
}
