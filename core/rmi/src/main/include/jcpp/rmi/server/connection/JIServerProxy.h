#ifndef JCPP_RMI_SERVER_CONNECTION_JISERVERPROXY_H
#define JCPP_RMI_SERVER_CONNECTION_JISERVERPROXY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JIServer.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/util/JList.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IServerProxy", simpleName="IServerProxy");
                class JCPP_EXPORT JIServerProxy : public JProxy, public JIServer{

                public:
                    JIServerProxy();

                    static JClass* getClazz();

                    virtual JObject* lookup(JEndPoint* endPoint, JClass* clazz);

                    virtual JIRegistry* getIRegistry();

                    virtual JIGC* getGC();

                    virtual JIGCClient* getGCClient();

                    virtual ~JIServerProxy();
                };
            }
        }
    }
}

#endif
