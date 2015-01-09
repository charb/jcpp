#include "jcpp/xml/internal/parser/JExternalEntity.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JExternalEntity::JExternalEntity(JLocator* l):JEntityDecl(getClazz()){
                    systemId=null;
                    publicId=null;
                    notation=null;
                    verbatimSystemId=null;
                }

                JInputSource* JExternalEntity::getInputSource(JEntityResolver* r){
                    JInputSource* retval = r->resolveEntity(publicId, systemId);
                    if (retval == null){
                        retval=null;//TODO JResolver::createInputSource(systemId, null);
                    }
                    return retval;
                }

                JExternalEntity::~JExternalEntity(){
                }
            }
        }
    }
}
