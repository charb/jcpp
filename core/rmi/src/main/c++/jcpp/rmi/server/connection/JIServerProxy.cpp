#include "jcpp/rmi/server/connection/JIServerProxy.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/JArrayList.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JIServerProxy::JIServerProxy():JProxy(getClazz()){
                }

                JObject* JIServerProxy::lookup(JEndPoint* endPoint, JClass* clazz){
                    JList* args=new JArrayList(); 
                    args->add(endPoint);
                    args->add(clazz);

                    JList* types=new JArrayList();
                    types->add(JEndPoint::getClazz());
                    types->add(JClass::getClazz());

                    return invoke(new JString("lookup"),types,args);
                }

                JIRegistry* JIServerProxy::getIRegistry(){
                    JList* args=new JArrayList();
                    JList* types=new JArrayList();

                    return dynamic_cast<JIRegistry*>(invoke(new JString("getIRegistry"),types,args));
                }

                JIGC* JIServerProxy::getGC(){
                    JList* args=new JArrayList();
                    JList* types=new JArrayList();

                    return dynamic_cast<JIGC*>(invoke(new JString("getGC"),types,args));
                }

                JIGCClient* JIServerProxy::getGCClient(){
                    JList* args=new JArrayList();
                    JList* types=new JArrayList();

                    return dynamic_cast<JIGCClient*>(invoke(new JString("getGCClient"),types,args));
                }

                JIServerProxy::~JIServerProxy(){
                }
            }
        }
    }
}


