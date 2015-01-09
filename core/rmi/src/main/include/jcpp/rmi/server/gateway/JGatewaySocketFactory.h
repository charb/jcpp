#ifndef JCPP_RMI_SERVER_GATEWAY_JGATEWAYSOCKETFACTORY_H
#define JCPP_RMI_SERVER_GATEWAY_JGATEWAYSOCKETFACTORY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/net/JServerSocket.h"
#include "jcpp/rmi/server/gateway/JRoute.h"
#include "jcpp/rmi/server/gateway/JGatewayConfiguration.h"

using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.GatewaySocketFactory", simpleName="GatewaySocketFactory");
                class JCPP_EXPORT JGatewaySocketFactory : public JObject{
                public:
                    static JClass* getClazz();

                    static JSocket* createSocket(JRoute* route,JGatewayConfiguration* gatewayConfiguration);

                    static JServerSocket* createServerSocket(JString* host, jint port,JGatewayConfiguration* gatewayConfiguration);

                    virtual ~JGatewaySocketFactory();
                };
            }
        }
    }
}

#endif
