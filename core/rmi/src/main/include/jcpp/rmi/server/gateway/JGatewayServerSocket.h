#ifndef JCPP_RMI_SERVER_GATEWAY_JGATEWAYSERVERSOCKET_H
#define JCPP_RMI_SERVER_GATEWAY_JGATEWAYSERVERSOCKET_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/net/JServerSocket.h"
#include "jcpp/net/JSocket.h"
#include "jcpp/rmi/server/gateway/JGatewayConfiguration.h"

using namespace jcpp::net;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{
            // @Class(canonicalName="jcpp.rmi.server.gateway.GatewayServerSocket", simpleName="GatewayServerSocket");
                class JCPP_EXPORT JGatewayServerSocket : public JServerSocket{
                    protected:
                        JGatewayConfiguration* gatewayConfiguration;

                    public:
                        JGatewayServerSocket(JString* host, jint port,JGatewayConfiguration* gatewayConfiguration);

                        static JClass* getClazz();

                        virtual JSocket* accept();

                        virtual JString* toString();

                        virtual ~JGatewayServerSocket();
                };
            }
        }
    }
}

#endif
