#include "jcpp/rmi/server/connection/JIRegistryProxy.h"
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

                JIRegistryProxy::JIRegistryProxy():JProxy(getClazz()){
                }

                void JIRegistryProxy::bind(JString* id, JObject* object, JList* interfaces){
                    JList* args=new JArrayList();
                    args->add(id);
                    args->add(object);
                    args->add(dynamic_cast<JObject*>(interfaces));

                    JList* types=new JArrayList();
                    types->add(JString::getClazz());
                    types->add(JObject::getClazz());
                    types->add(JList::getClazz());
                    invoke(new JString("bind"),types,args);
                }

                JPrimitiveObjectArray* JIRegistryProxy::list(){
                    JList* args=new JArrayList();
                    JList* types=new JArrayList();
                    return dynamic_cast<JPrimitiveObjectArray*>(invoke(new JString("list"),types,args));
                }

                JObject* JIRegistryProxy::lookup(JString* id){
                    JList* args=new JArrayList();
                    args->add(id);

                    JList* types=new JArrayList();
                    types->add(JString::getClazz());
                    return invoke(new JString("lookup"),types,args);
                }

                void JIRegistryProxy::rebind(JString* id, JObject* object, JList* interfaces){
                    JList* args=new JArrayList();
                    args->add(id);
                    args->add(object);
                    args->add(dynamic_cast<JObject*>(interfaces));

                    JList* types=new JArrayList();
                    types->add(JString::getClazz());
                    types->add(JObject::getClazz());
                    types->add(JList::getClazz());
                    invoke(new JString("rebind"),types,args);
                }

                void JIRegistryProxy::unbind(JString* id){
                    JList* args=new JArrayList();
                    args->add(id);

                    JList* types=new JArrayList();
                    types->add(JString::getClazz());
                    invoke(new JString("unbind"),types,args);
                }

                JIRegistryProxy::~JIRegistryProxy(){
                }
            }
        }
    }
}

