#ifndef JCPP_RMI_SERVER_CONNECTION_JISERVER_H
#define JCPP_RMI_SERVER_CONNECTION_JISERVER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/connection/JIRegistry.h"
#include "jcpp/rmi/server/connection/JIGCClient.h"
#include "jcpp/rmi/server/connection/JIGC.h"

using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.IServer", simpleName="IServer");
                class JCPP_EXPORT JIServer : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual JObject* lookup(JEndPoint* endPoint, JClass* clazz)=0;

                    virtual JIRegistry* getIRegistry()=0;

                    virtual JIGC* getGC()=0;

                    virtual JIGCClient* getGCClient()=0;

                    virtual ~JIServer();
                };
            }
        }
    }
}
#endif
