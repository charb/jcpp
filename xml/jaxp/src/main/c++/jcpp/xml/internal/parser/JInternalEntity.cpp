#include "jcpp/xml/internal/parser/JInternalEntity.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JInternalEntity::JInternalEntity(JString* name,JPrimitiveCharArray* value):JEntityDecl(getClazz()){
                    this->name=name;
                    this->buf=value;
                }

                JInternalEntity::~JInternalEntity(){
                }
            }
        }
    }
}
