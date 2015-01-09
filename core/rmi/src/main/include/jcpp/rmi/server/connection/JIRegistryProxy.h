#ifndef JCPP_RMI_SERVER_CONNECTION_JIREGISTRYPROXY_H
#define JCPP_RMI_SERVER_CONNECTION_JIREGISTRYPROXY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/connection/JIRegistry.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IRegistryProxy", simpleName="IRegistryProxy");
                class JCPP_EXPORT JIRegistryProxy : public JProxy, public JIRegistry{

                public:
                    JIRegistryProxy();

                    static JClass* getClazz();

                    virtual void bind(JString* id, JObject* object, JList* interfaces);

                    virtual JPrimitiveObjectArray* list();

                    virtual JObject* lookup(JString* id);

                    virtual void rebind(JString* id, JObject* object, JList* interfaces);

                    virtual void unbind(JString* id);

                    virtual ~JIRegistryProxy();
                };
            }
        }
    }
}

#endif
