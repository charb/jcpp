#include "jcpp/xml/internal/parser/JElementDecl.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JElementDecl::JElementDecl(JString* s):JObject(getClazz()){
                    name=s;
                    id=null;
                    contentType=null;
                    validator=null;
                    model=null;
                    ignoreWhitespace=false;
                    isFromInternalSubset=false;
                    attributes=new JHashtable();
                }

                JElementDecl::~JElementDecl(){
                }
            }
        }
    }
}
