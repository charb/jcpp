#include "jcpp/xml/internal/parser/JEntityDecl.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JEntityDecl::JEntityDecl(JClass* _class):JObject(_class){
                    name=null;
                    isFromInternalSubset=false;
                    isPE=false;
                }
    
                JEntityDecl::JEntityDecl():JObject(getClazz()){
                    name=null;
                    isFromInternalSubset=false;
                    isPE=false;
                }

                JEntityDecl::~JEntityDecl(){
                }
            }
        }
    }
}
