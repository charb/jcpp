#include "jcpp/rmi/server/gateway/JGatewaySocketFactory.h"
#include "jcpp/rmi/server/gateway/JGatewaySocket.h"
#include "jcpp/rmi/server/gateway/JGatewayServerSocket.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace gateway{

                JSocket* JGatewaySocketFactory::createSocket(JRoute* route,JGatewayConfiguration* gatewayConfiguration){
                    if (route!=null && route->isHttp()){
                        return null;//TODO HttpRequestGatewaySocket
                    }else{
                        return new JGatewaySocket(route,gatewayConfiguration);
                    }
                }

                JServerSocket* JGatewaySocketFactory::createServerSocket(JString* host, jint port,JGatewayConfiguration* gatewayConfiguration){
                    return new JGatewayServerSocket(host,port,gatewayConfiguration);
                }

                JGatewaySocketFactory::~JGatewaySocketFactory(){
                }
            }
        }
    }
}


