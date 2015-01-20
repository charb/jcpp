#include "jcpp/rmi/server/connection/JIGCProxy.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                

                JIGCProxy::JIGCProxy():JProxy(getClazz()){
                }

                JPrimitiveBooleanArray* JIGCProxy::ping(JEndPoint* endPoint, JPrimitiveObjectArray* id){
                    JList* args=new JArrayList();
                    args->add(endPoint);
                    args->add(id);

                    JList* types=new JArrayList();
                    types->add(JEndPoint::getClazz());
                    types->add(JPrimitiveObjectArray::getClazz());
                    return dynamic_cast<JPrimitiveBooleanArray*>(invoke(new JString("ping"),types,args));
                }

                void JIGCProxy::endPointDead(JEndPoint* endPoint){
                    JList* args=new JArrayList();
                    args->add(endPoint);

                    JList* types=new JArrayList();
                    types->add(JEndPoint::getClazz());
                    invoke(new JString("endPointDead"),types,args);
                }

                JPrimitiveObjectArray* JIGCProxy::getExportedEndPoints(){
                    JList* args=new JArrayList();
                    JList* types=new JArrayList();
                    return dynamic_cast<JPrimitiveObjectArray*>(invoke(new JString("getExportedEndPoints"),types,args));
                }

                JIGCProxy::~JIGCProxy(){
                }
            }
        }
    }
}


