#ifndef JCPP_RMI_SERVER_CONNECTION_JREGISTRY_H
#define JCPP_RMI_SERVER_CONNECTION_JREGISTRY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/connection/JIRegistry.h"
#include "jcpp/rmi/server/connection/JIGCClient.h"
#include "jcpp/rmi/server/connection/JIGC.h"
#include "jcpp/rmi/server/connection/JILifecycle.h"
#include "jcpp/rmi/server/connection/JIInvocationListener.h"
#include "jcpp/rmi/server/connection/JObjectInformations.h"
#include "jcpp/util/JList.h"

using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.Registry", simpleName="Registry");
                class JCPP_EXPORT JRegistry: public JObject, public JIRegistry{
                protected:
                    JObjectInformations* objectInformations;

                public:
                    JRegistry(JObjectInformations* objectInformations);

                    static JClass* getClazz();

                    virtual void bind(JString* id, JObject* object, JList* interfaces);

                    virtual JPrimitiveObjectArray* list();

                    virtual JObject* lookup(JString* id);

                    virtual void rebind(JString* id, JObject* object, JList* interfaces);

                    virtual void unbind(JString* id);

                    virtual ~JRegistry();
                };
            }
        }
    }
}
#endif
