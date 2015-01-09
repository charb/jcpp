#ifndef JCPP_RMI_SERVER_CONNECTION_JIGCCLIENTPROXY_H
#define JCPP_RMI_SERVER_CONNECTION_JIGCCLIENTPROXY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/connection/JIGCClient.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IGCClientProxy", simpleName="IGCClientProxy");
                class JCPP_EXPORT JIGCClientProxy : public JProxy, public JIGCClient{

                public:
                    JIGCClientProxy();

                    static JClass* getClazz();

                    virtual JPrimitiveObjectArray* getEndPoints();

                    virtual ~JIGCClientProxy();
                };
            }
        }
    }
}

#endif
