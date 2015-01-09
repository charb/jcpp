#include "jcpp/rmi/server/connection/JIGCClientProxy.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JIGCClientProxy::JIGCClientProxy():JProxy(getClazz()){
                }

                JPrimitiveObjectArray* JIGCClientProxy::getEndPoints(){
                    JList* args=new JArrayList();
                    return dynamic_cast<JPrimitiveObjectArray*>(invoke(new JString("getEndPoints"),null,args));
                }

                JIGCClientProxy::~JIGCClientProxy(){
                }
            }
        }
    }
}



