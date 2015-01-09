#include "jcpp/xml/internal/parser/JAttributeDecl.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{
                JString* JAttributeDecl::CDATA = new JString("CDATA");
                JString* JAttributeDecl::ID = new JString("ID");
                JString* JAttributeDecl::IDREF = new JString("IDREF");
                JString* JAttributeDecl::IDREFS = new JString("IDREFS");
                JString* JAttributeDecl::ENTITY = new JString("ENTITY");
                JString* JAttributeDecl::ENTITIES = new JString("ENTITIES");
                JString* JAttributeDecl::NMTOKEN = new JString("NMTOKEN");
                JString* JAttributeDecl::NMTOKENS = new JString("NMTOKENS");
                JString* JAttributeDecl::NOTATION = new JString("NOTATION");
                JString* JAttributeDecl::ENUMERATION = new JString("ENUMERATION");
                JString* JAttributeDecl::IMPLIED = new JString("#IMPLIED");
                JString* JAttributeDecl::REQUIRED = new JString("#REQUIRED");
                JString* JAttributeDecl::FIXED = new JString("#FIXED");

                JAttributeDecl::JAttributeDecl(JString* s):JObject(getClazz()){
                    name=s;
                    type=null;
                    values=null;
                    defaultValue=null;
                    isRequired=false;
                    isFixed=false;
                    isFromInternalSubset=false;
                    valueDefault=null;
                }

                JAttributeDecl::~JAttributeDecl(){
                }
            }
        }
    }
}
